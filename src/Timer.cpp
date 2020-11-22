#include "Timer.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using pomodoro::Timer;

Timer::Timer(int delayInMs_) : delayInMs(delayInMs_) { }

Timer::~Timer() = default;

void Timer::start()
{
    std::thread t([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
        std::cout << "End of Timer" << std::endl;
    });
    t.detach();
}
