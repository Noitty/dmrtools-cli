#include <deque>
#include <vector>

using namespace std;

class Serial
{
public:
    deque<char> fifo;
    int messages;
    Serial(string portname, int speed, int parity);
    void readPort();
    void writePort(vector<char> &v);
    string getMessage();
private:
    int fd;
};
