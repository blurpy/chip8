#include <iostream>

#include "Timer.h"

Timer::Timer() {
    std::cout << "Timer in" << std::endl;
}

Timer::~Timer() {
    std::cout << "Timer out" << std::endl;
}

void Timer::init() {
    counter = 0;
    lastTick = std::chrono::steady_clock::now();
}

/*
 * Returns true every ~16ms (60Hz).
 */
bool Timer::tick() {
    bool incremented = false;

    auto currentTick = std::chrono::steady_clock::now();
    auto timeSinceLastTick = currentTick - lastTick;
    auto timeSinceLastTickNano = std::chrono::duration_cast<std::chrono::nanoseconds>(timeSinceLastTick);

    lastTick = currentTick;
    counter += timeSinceLastTickNano.count();

    if (counter > FREQUENCY) {
        incremented = true;
        counter %= FREQUENCY;
    }

    return incremented;
}
