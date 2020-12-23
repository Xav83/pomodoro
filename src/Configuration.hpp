#pragma once

#include "Timers.hpp"
#include "color/Set.hpp"
#include "utility/NumbersDictionary.hpp"

namespace pomodoro {
class Configuration {
public:
  Configuration(pomodoro::color::Set colors_, std::chrono::minutes work_time_,
                std::chrono::minutes break_time_,
                std::chrono::minutes long_break_time_);
  ~Configuration();

  color::Set getColors() const;
  std::chrono::minutes getWorkTime() const;
  std::chrono::minutes getBreakTime() const;
  std::chrono::minutes getLongBreakTime() const;

private:
  color::Set colors;
  std::chrono::minutes work_time =
      std::chrono::minutes(pomodoro::numbers::default_work_time);
  std::chrono::minutes break_time =
      std::chrono::minutes(pomodoro::numbers::default_break_time);
  std::chrono::minutes long_break_time =
      std::chrono::minutes(pomodoro::numbers::default_long_break_time);
};
} // namespace pomodoro
