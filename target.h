#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <chrono>
#include <boost/asio.hpp>

struct target {
    std::string host;
    std::string addr;
    int port;
    std::chrono::milliseconds ping_milliseconds;
    std::chrono::microseconds ping_microseconds;
};

#endif // TARGET_H
