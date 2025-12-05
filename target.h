#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <chrono>

struct target {
    std::string host;
    int port;
    std::chrono::milliseconds last_ping;
};

#endif // TARGET_H
