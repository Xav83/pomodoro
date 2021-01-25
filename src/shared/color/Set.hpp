#pragma once

#include <fmt/color.h>

namespace pomodoro::color {
struct Set {
  fmt::color work_color;
  fmt::color break_color;

  bool operator==(const Set &other) const {
    return work_color == other.work_color && break_color == other.break_color;
  }
};
} // namespace pomodoro::color
