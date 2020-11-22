#pragma once

#include "Timer.hpp"
#include <string_view>
#include <vector>

namespace pomodoro
{
class Timers
{
public:
    Timers();
    ~Timers();

    void emplaceTimer(std::string_view name, int delayInMs);

    Timer& getTimer(size_t index);

    bool hasOneTimerRunning() const;

private:
    std::vector<Timer> timers;
};
}
