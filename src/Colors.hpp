#pragma once

#include "ColorSet.hpp"
#include <array>

namespace pomodoro {
constexpr std::array<pomodoro::ColorSet, 2> colors{{
    {fmt::color::cadet_blue, fmt::color::golden_rod},
    {fmt::color::light_coral, fmt::color::light_blue},
}};
}
