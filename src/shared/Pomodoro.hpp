#pragma once

#include "Timers.hpp"
#include "color/Dictionary.hpp"
#include <utility>

namespace pomodoro {
class Configuration;
}

class Pomodoro {
public:
  explicit Pomodoro(const pomodoro::Configuration &configuration,
                    std::function<void()> work_timer_callback,
                    std::function<void()> break_timer_callback,
                    std::function<void()> long_break_timer_callback);
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  pomodoro::color::Id color_id;
};
