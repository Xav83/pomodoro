#pragma once

#include "Timer.hpp"
#include <string_view>
#include <vector>

namespace pomodoro {
class Timers {
public:
  Timers();
  ~Timers();

  void emplaceTimer(
      std::string_view name, std::chrono::milliseconds delayInMs,
      std::function<void()> callback = []() {});

  Timer &getTimer(size_t index);

  std::vector<pomodoro::Timer>::const_iterator cbegin() const;
  std::vector<pomodoro::Timer>::const_iterator cend() const;

  bool hasOneTimerRunning() const;

private:
  std::vector<Timer> timers;
};
} // namespace pomodoro
