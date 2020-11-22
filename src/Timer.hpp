#pragma once

#include <chrono>
#include <string_view>

namespace pomodoro
{
class Timer
{
public:
    Timer(std::string_view name, std::chrono::milliseconds delayInMs);
    ~Timer();

    void start();

    bool isRunning() const;

    std::chrono::seconds getRemainingTime() const;
    std::string_view getName() const;

private:
    std::string_view name;
    std::chrono::milliseconds delayInMs{0};
    bool isCurrentlyRunning{false}, hasRun{false};
    std::chrono::time_point<std::chrono::high_resolution_clock> timeAtStart;
};
}
