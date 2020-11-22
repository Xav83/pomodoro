#include "Timers.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    pomodoro::Timers t;
    t.emplaceTimer("Work", 10000);
    t.emplaceTimer("Break", 1000);

    t.getTimer(0).start();
    t.getTimer(1).start();

    while(t.hasOneTimerRunning());
    return 0;
}
