#include "Configuration.hpp"

using pomodoro::Configuration;

Configuration::Configuration(pomodoro::color::Set colors_,
                             std::chrono::minutes work_time_,
                             std::chrono::minutes break_time_,
                             std::chrono::minutes long_break_time_)
    : colors(colors_), work_time(work_time_), break_time(break_time_),
      long_break_time(long_break_time_) {}

Configuration::~Configuration() = default;

pomodoro::color::Set Configuration::getColors() const { return colors; }

std::chrono::minutes Configuration::getWorkTime() const { return work_time; }

std::chrono::minutes Configuration::getBreakTime() const { return break_time; }

std::chrono::minutes Configuration::getLongBreakTime() const {
  return long_break_time;
}
