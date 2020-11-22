#include "Timer.hpp"
#include <chrono>
#include <thread>

using pomodoro::Timer;

Timer::Timer() = default;
Timer::~Timer() = default;

void Timer::setTimeoutIn(int delayInMs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
}
