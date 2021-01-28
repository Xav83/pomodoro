#include "Timers.hpp"
#include <algorithm>
#include <cassert>

using pomodoro::Timer;
using pomodoro::Timers;

Timers::Timers() = default;
Timers::~Timers() = default;

void Timers::emplaceTimer(std::string_view name,
                          std::chrono::milliseconds delayInMs,
                          std::function<void()> callback) {
  timers.emplace_back(name, delayInMs, callback);
}

Timer &Timers::getTimer(size_t index) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(index < timers.size());
  return timers[index];
}

const Timer &Timers::getTimer(size_t index) const {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(index < timers.size());
  return timers[index];
}

std::vector<pomodoro::Timer>::const_iterator Timers::cbegin() const {
  return std::cbegin(timers);
}

std::vector<pomodoro::Timer>::const_iterator Timers::cend() const {
  return std::cend(timers);
}

bool Timers::hasOneTimerRunning() const {
  return std::any_of(std::begin(timers), std::end(timers),
                     [](const auto &timer) { return timer.isRunning(); });
}
