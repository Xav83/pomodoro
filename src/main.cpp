#include "Timers.hpp"
#include <fmt/chrono.h>
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    pomodoro::Timers timers;
    timers.emplaceTimer("Work", std::chrono::minutes(25), [&timers](){ timers.getTimer(1).start(); });
    timers.emplaceTimer("Break", std::chrono::minutes(5), [&timers](){ timers.getTimer(0).start(); });

    timers.getTimer(0).start();

    while(timers.hasOneTimerRunning())
    {
        for(const auto& t : timers.getTimers())
        {
            if(t.isRunning())
            {
                fmt::print("Timer \"{}\" - Time remaining: {:%M:%S}\n", t.getName(), t.getRemainingTime());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
