#pragma once

#include <string_view>

namespace pomodoro
{
class Timer
{
public:
    Timer(std::string_view name, int delayInMs);
    ~Timer();

    void start();

    bool isRunning() const;

private:
    std::string_view name;
    int delayInMs{0};
    bool isCurrentlyRunning{false}, hasRun{false};
};
}
