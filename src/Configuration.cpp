#include "Configuration.hpp"
#include <cassert>

using pomodoro::Configuration;

Configuration::Configuration() = default;

Configuration::Configuration(pomodoro::color::Id color_id_,
                             std::chrono::minutes work_time_,
                             std::chrono::minutes break_time_,
                             std::chrono::minutes long_break_time_)
    : color_id(color_id_), work_time(work_time_), break_time(break_time_),
      long_break_time(long_break_time_) {}

Configuration::~Configuration() = default;

void Configuration::setColorId(pomodoro::color::Id color_id_) {
  color_id = color_id_;
}

pomodoro::color::Id Configuration::getColorId() const { return color_id; }

pomodoro::color::Set Configuration::getColors() const {
  if (color_id == pomodoro::color::Id::no_color) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    assert(false);
    return pomodoro::color::dictionary.at(0);
  }
  return pomodoro::color::dictionary.at(static_cast<size_t>(color_id));
}

void Configuration::setWorkTime(std::chrono::minutes work_time_) {
  work_time = work_time_;
}

std::chrono::minutes Configuration::getWorkTime() const { return work_time; }

void Configuration::setBreakTime(std::chrono::minutes break_time_) {
  break_time = break_time_;
}

std::chrono::minutes Configuration::getBreakTime() const { return break_time; }

void Configuration::setLongBreakTime(std::chrono::minutes long_break_time_) {
  long_break_time = long_break_time_;
}

std::chrono::minutes Configuration::getLongBreakTime() const {
  return long_break_time;
}
