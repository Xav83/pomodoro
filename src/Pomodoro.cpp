#include "Pomodoro.hpp"
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <cassert>
#include <filesystem>

Pomodoro::Pomodoro()
{
    std::filesystem::path start_break_sound_file("C:/ProgramData/pomodoro/PowerDown1.ogg");
    std::filesystem::path start_work_sound_file("C:/ProgramData/pomodoro/PowerUp1.ogg");
    assert(std::filesystem::exists(start_break_sound_file));
    assert(std::filesystem::exists(start_work_sound_file));
    start_break_sound.openFromFile(start_break_sound_file.string());
    start_work_sound.openFromFile(start_work_sound_file.string());

    timers.emplaceTimer("Work", std::chrono::minutes(25), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(1).start(); });
    timers.emplaceTimer("Break", std::chrono::minutes(5), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(2).start(); });
    timers.emplaceTimer("Work", std::chrono::minutes(25), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(3).start(); });
    timers.emplaceTimer("Break", std::chrono::minutes(5), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(4).start(); });
    timers.emplaceTimer("Work", std::chrono::minutes(25), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(5).start(); });
    timers.emplaceTimer("Break", std::chrono::minutes(5), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(6).start(); });
    timers.emplaceTimer("Work", std::chrono::minutes(25), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(7).start(); });
    timers.emplaceTimer("Break", std::chrono::minutes(15), [this](){ start_break_sound.stop(); start_break_sound.play(); fmt::print("\n"); timers.getTimer(0).start(); });
}

Pomodoro::~Pomodoro() = default;

void Pomodoro::run()
{
    timers.getTimer(0).start();
}

bool Pomodoro::isRunning() const
{
    return timers.hasOneTimerRunning();
}

std::string Pomodoro::getCurrentState() const
{
    if(! isRunning())
    {
        return "The Pomodoro has not been started.";
    }
    const auto& rawTimers = timers.getTimers();
    const auto it = std::find_if(std::begin(rawTimers), std::end(rawTimers), [](const auto& timer){ return timer.isRunning(); });
    assert(it != std::end(rawTimers));

    return fmt::format("Timer \"{}\" - Time remaining: {:%M:%S}", it->getName().data(), it->getRemainingTime());
}