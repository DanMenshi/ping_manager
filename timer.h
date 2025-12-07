#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class timer
{
public:
    void start_time();
    void end_time();
    void reset();
    std::chrono::milliseconds get_ms();
    std::chrono::microseconds get_mcs();
private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
};

#endif // TIMER_H
