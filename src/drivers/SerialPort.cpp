#include <cstring>
#include <cerrno>
#include <cstdio>

#include <iostream>
#include <deque>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "serial.h"

using namespace std;

mutex fifo_mutex;

static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

Serial::Serial (string portname, int speed, int parity) : messages(0)
{
  fd = open (portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    fprintf(stderr, "Error opening serial port %s\n", portname.c_str());
    return;
  }

  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr(fd, &tty) != 0) {
    fprintf(stderr, "Error %d from tcgetattr: %s\n", errno, strerror(errno));
    return;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
  tty.c_iflag &= ~IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 5;

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~(PARENB | PARODD);
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    fprintf(stderr, "Error %d from tcsetattr: %s\n", errno, strerror(errno));
  }
}

void Serial::readPort()
{
  if (fd<0)
    return;

  vector<char> v(100);
  int n = read(fd, &v[0], 100);
  v.resize(n);

  fifo_mutex.lock();
  for (auto i : v) {
    fifo.push_back(i);
    if (i == '#')
      messages++;
  }
  fifo_mutex.unlock();
}

void Serial::writePort(vector<char> &v)
{
  if (fd<0)
    return;

  int n = write(fd, &v[0], v.size());
  if (n < 0)
    cerr << "Write error" << endl;
}

string Serial::getMessage()
{
    if (messages <= 0)
        return "";

    deque<char>::iterator iter = fifo.begin();
    while(*iter != '#')
    iter++;

    string s(fifo.begin(), iter);

    iter++;

    fifo_mutex.lock();
    fifo.erase(fifo.begin(), iter);
    messages--;
    fifo_mutex.unlock();
    cout << '"' << trim(s) << '"' << endl;
    return s;
}

int main()
{
  Serial s("/dev/ttyS1", B9600, 0);
  thread t([&s](){
      while (1) {
  s.readPort();
  this_thread::sleep_for(chrono::milliseconds(200));
      }
    });
  while (1) {
    sleep(1);
    while (s.getMessage() != "");
  }
  return 0;
}
