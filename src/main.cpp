#include "Timers.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    pomodoro::Timers t;
    t.emplaceTimer(10000);
    t.emplaceTimer(1000);

    std::cout << "Hello..." ;

    t.getTimer(0).start();
    t.getTimer(1).start();

    std::cout << "World !" << std::endl;

    while(t.hasOneTimerRunning());
    return 0;
}
