#pragma once

#include "Set.hpp"
#include "shared/utility/NumbersDictionary.hpp"
#include <array>

namespace pomodoro::color {
constexpr std::array<pomodoro::color::Set, pomodoro::numbers::number_of_colors>
    dictionary{{
        {fmt::color::cadet_blue, fmt::color::golden_rod},
        {fmt::color::light_coral, fmt::color::light_blue},
        {fmt::color::white, fmt::color::white},
        {fmt::color::green, fmt::color::green},
        {fmt::color::black, fmt::color::black},
    }};

enum class Id : int {
  no_color = -1,
  default_1,
  default_2,
  white,
  green,
  black,
  _Size
};
} // namespace pomodoro::color

static_assert(static_cast<size_t>(pomodoro::color::Id::_Size) ==
                  pomodoro::color::dictionary.size(),
              "Each entry in the pomodoro::color::dictionary must have its "
              "matching pomodoro::color::Id in the enum.");
