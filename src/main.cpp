#include "Pomodoro.hpp"
#include <SFML/Audio.hpp>
#include <fmt/chrono.h>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
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
