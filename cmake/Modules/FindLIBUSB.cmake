include(FindPackageHandleStandardArgs)

# Get the HINTS that may help
execute_process(COMMAND pkg-config --cflags libusb-1.0 OUTPUT_VARIABLE LIBUSB_PATH)
string(REPLACE "\n" "" LIBUSB_PATH ${LIBUSB_PATH})
string(REPLACE "-I" "" LIBUSB_PATH ${LIBUSB_PATH})

# Find the headers location for LIBUSB.
if(NOT LIBUSB_FIND_QUIETLY)
    message(STATUS "Looking for LIBUSB header: libusb.h")
endif()
find_path(LIBUSB_INCLUDE_DIR 1.0 EXACT
    NAME libusb.h
    HINTS ${LIBUSB_PATH} $ENV{LIBUSB_PATH}
    PATH_SUFFIXES include
    PATHS /usr /usr/local
)
if(NOT LIBUSB_FIND_QUIETLY)
    if(LIBUSB_INCLUDE_DIR)
        message(STATUS "Looking for LIBUSB header: libusb.h - found")
    else()
        message(STATUS "Looking for LIBUSB header: libusb.h - not found")
    endif()
endif()

# Find the SOIL library.
if(NOT LIBUSB_FIND_QUIETLY)
    message(STATUS "Looking for LIBUSB libraries")
endif()
find_library(LIBUSB_LIBRARY
    NAME libusb-1.0.so
    HINTS ${LIBUSB_PATH} $ENV{LD_LIBRARY_PATH} $ENV{LIBUSB_PATH}
    PATH_SUFFIXES lib64 lib lib64/x86_64-linux-gnu lib/x86_64-linux-gnu
    PATHS /opt /usr /usr/local
)
if(NOT LIBUSB_FIND_QUIETLY)
    if(LIBUSB_LIBRARY)
        message(STATUS "Looking for LIBUSB libraries - found")
    else()
        message(STATUS "Looking for LIBUSB libraries - not found")
    endif()
endif()

# Library + Include Directories
if(LIBUSB_LIBRARY AND LIBUSB_INCLUDE_DIR)
    get_filename_component(LIBUSB_LIBRARY_DIR ${LIBUSB_LIBRARY} PATH)
    if(NOT LIBUSB_FIND_QUIETLY)
        message(STATUS "LIBUSB libraries directory is ${LIBUSB_LIBRARY_DIR}")
    endif()
    set(LIBUSB_INCLUDE_DIRS ${LIBUSB_INCLUDE_DIR})
    set(LIBUSB_FOUND TRUE)
    set(LIBUSB_LIBRARIES ${LIBUSB_LIBRARY})
endif()

find_package_handle_standard_args(LIBUSB DEFAULT_MSG LIBUSB_LIBRARIES LIBUSB_INCLUDE_DIRS)
mark_as_advanced(LIBUSB_LIBRARIES LIBUSB_INCLUDE_DIRS)
