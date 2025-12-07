#include "timer.h"

void timer::start_time() {
    start = std::chrono::high_resolution_clock::now();
}
void timer::end_time() {
    end = std::chrono::high_resolution_clock::now();
}

void timer::reset() {
    start = std::chrono::high_resolution_clock::time_point();
    end = std::chrono::high_resolution_clock::time_point();
}

std::chrono::milliseconds timer::get_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

std::chrono::microseconds timer::get_mcs() {
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}
