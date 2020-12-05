#pragma once

#include "Set.hpp"
#include <array>

namespace pomodoro::color {
constexpr std::array<pomodoro::color::Set, 5> dictionary{{
    {fmt::color::cadet_blue, fmt::color::golden_rod},
    {fmt::color::light_coral, fmt::color::light_blue},
    {fmt::color::white, fmt::color::white},
    {fmt::color::green, fmt::color::green},
    {fmt::color::black, fmt::color::black},
}};
}
