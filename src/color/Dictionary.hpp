#pragma once

#include "Set.hpp"
#include <array>

namespace pomodoro::color {
constexpr std::array<pomodoro::color::Set, 2> dictionary{{
    {fmt::color::cadet_blue, fmt::color::golden_rod},
    {fmt::color::light_coral, fmt::color::light_blue},
}};
}
