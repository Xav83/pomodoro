#include "Timer.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using pomodoro::Timer;

Timer::Timer(std::string_view name_, std::chrono::milliseconds delayInMs_) : name(name_), delayInMs(delayInMs_) { }

Timer::~Timer() = default;

void Timer::start()
{
    std::cout << "Starting the timer " << name << std::endl;
    isCurrentlyRunning = true;
    timeAtStart = std::chrono::high_resolution_clock::now();
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

std::chrono::seconds Timer::getRemainingTime() const
{
    if(isRunning())
    {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(delayInMs - (std::chrono::high_resolution_clock::now() - timeAtStart));
        return elapsed;
    }
    return std::chrono::seconds(0);
}

std::string_view Timer::getName() const
{
    return name;
}
