#pragma once

#include "Timer.hpp"
#include <vector>

namespace pomodoro
{
class Timers
{
public:
    Timers();
    ~Timers();

    void emplaceTimer(int delayInMs);

    Timer& getTimer(size_t index);

private:
    std::vector<Timer> timers;
};
}