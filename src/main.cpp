#include "Pomodoro.hpp"
#include <fmt/core.h>
#include <thread>

int main()
{
    Pomodoro pomodoro;
    pomodoro.run();

    while(pomodoro.isRunning())
    {
        fmt::print("\r{}", pomodoro.getCurrentState());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
