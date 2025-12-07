#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <chrono>
#include <boost/asio.hpp>

struct target {
    std::string host;
    boost::asio::ip::address_v4 ip_v4;
    int port;
    std::chrono::milliseconds ping_milliseconds;
    std::chrono::microseconds ping_microseconds;
};

#endif // TARGET_H
