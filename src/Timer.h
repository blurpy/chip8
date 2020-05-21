#ifndef CHIP8_TIMER_H
#define CHIP8_TIMER_H

#include <chrono>

class Timer {

public:
    static const int FREQUENCY = (int) (1.0 / 60.0 * 1000.0 * 1000.0 * 1000.0); // 60 Hz - in nanoseconds

    Timer();
    ~Timer();

    void init();
    bool tick();

private:
    int64_t counter;
    std::chrono::steady_clock::time_point lastTick;
};

#endif //CHIP8_TIMER_H
