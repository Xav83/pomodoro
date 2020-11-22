#include "Timer.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using pomodoro::Timer;

Timer::Timer(std::string_view name_, int delayInMs_) : name(name_), delayInMs(delayInMs_) { }

Timer::~Timer() = default;

void Timer::start()
{
    std::cout << "Starting the timer " << name << std::endl;
    isCurrentlyRunning = true;
    std::thread t([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
        isCurrentlyRunning = false;
        hasRun = true;
        std::cout << "End of the timer " << name << std::endl;
    });
    t.detach();
}

bool Timer::isRunning() const
{
    return isCurrentlyRunning;
}
