#include "Timers.hpp"
#include <SFML/Audio.hpp>
#include <fmt/chrono.h>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

int main()
{
    pomodoro::Timers timers;
    sf::Music start_break_sound, start_work_sound;

    std::filesystem::path start_break_sound_file("C:/ProgramData/pomodoro/PowerDown1.ogg");
    std::filesystem::path start_work_sound_file("C:/ProgramData/pomodoro/PowerUp1.ogg");
    assert(std::filesystem::exists(start_break_sound_file));
    assert(std::filesystem::exists(start_work_sound_file));
    start_break_sound.openFromFile(start_break_sound_file.string());
    start_work_sound.openFromFile(start_work_sound_file.string());

    timers.emplaceTimer("Work", std::chrono::minutes(25),
        [&timers, &start_break_sound]()
        {
            start_break_sound.stop();
            start_break_sound.play();
            timers.getTimer(1).start();
        });
    timers.emplaceTimer("Break", std::chrono::minutes(5),
        [&timers, &start_work_sound]()
        {
            start_work_sound.stop();
            start_work_sound.play();
            timers.getTimer(0).start();
        });

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
