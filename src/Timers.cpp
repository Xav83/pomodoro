#include "Timers.hpp"
#include <algorithm>
#include <cassert>

using pomodoro::Timers;
using pomodoro::Timer;

Timers::Timers() = default;
Timers::~Timers() = default;

void Timers::emplaceTimer(std::string_view name, std::chrono::milliseconds delayInMs)
{
    timers.emplace_back(name, delayInMs);
}

Timer& Timers::getTimer(size_t index)
{
    assert(index < timers.size());
    return timers[index];
}

std::vector<Timer>& Timers::getTimers()
{
    return timers;
}

bool Timers::hasOneTimerRunning() const
{
    return std::any_of(std::begin(timers), std::end(timers), [](const auto& timer){ return timer.isRunning(); });
}
