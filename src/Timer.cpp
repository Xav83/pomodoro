#include "Timer.hpp"
#include <chrono>
#include <thread>

using pomodoro::Timer;

Timer::Timer(int delayInMs_) : delayInMs(delayInMs_) { }

Timer::~Timer() = default;

void Timer::start()
{
    isCurrentlyRunning = true;
    std::thread t([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
        isCurrentlyRunning = false;
        hasRun = true;
    });
    t.detach();
}

bool Timer::isRunning() const
{
    return isCurrentlyRunning;
}
