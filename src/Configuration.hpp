#pragma once

#include "Timers.hpp"
#include "color/Dictionary.hpp"
#include "utility/NumbersDictionary.hpp"

namespace pomodoro {
class Configuration {
public:
  Configuration();

  Configuration(pomodoro::color::Id color_id_, std::chrono::minutes work_time_,
                std::chrono::minutes break_time_,
                std::chrono::minutes long_break_time_);
  ~Configuration();

  void setColorId(pomodoro::color::Id color_id_);
  color::Id getColorId() const;
  color::Set getColors() const;

  void setWorkTime(std::chrono::minutes work_time_);
  std::chrono::minutes getWorkTime() const;

  void setBreakTime(std::chrono::minutes break_time_);
  std::chrono::minutes getBreakTime() const;

  void setLongBreakTime(std::chrono::minutes long_break_time_);
  std::chrono::minutes getLongBreakTime() const;

  bool operator==(const Configuration &other) const {
    return color_id == other.color_id and work_time == other.work_time and
           break_time == other.break_time and
           long_break_time == other.long_break_time;
  }

private:
  color::Id color_id = pomodoro::color::Id::default_1;
  std::chrono::minutes work_time =
      std::chrono::minutes(pomodoro::numbers::default_work_time);
  std::chrono::minutes break_time =
      std::chrono::minutes(pomodoro::numbers::default_break_time);
  std::chrono::minutes long_break_time =
      std::chrono::minutes(pomodoro::numbers::default_long_break_time);
};
} // namespace pomodoro
