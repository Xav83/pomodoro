#pragma once

#include "NumbersDictionary.hpp"
#include <string_view>

namespace pomodoro::strings {
const auto color_flag_help_message = fmt::format(
    "-c,--color=[0 - {}]\n"
    "  Sets the set of colors used for the work and break period.\n",
    pomodoro::numbers::number_of_colors - 1);
const auto work_flag_help_message =
    fmt::format("-w,--work=[1 - {}]\n"
                "  Sets the time of the work period.\n",
                std::numeric_limits<int>::max());
const auto break_flag_help_message =
    fmt::format("-b,--break=[1 - {}]\n"
                "  Sets the time of the (small) break period.\n",
                std::numeric_limits<int>::max());
const auto long_break_flag_help_message =
    fmt::format("-lb,--long-break=[1 - {}]\n"
                "  Sets the time of the long break period.\n",
                std::numeric_limits<int>::max());
const auto set_as_default_flag_help_message = fmt::format(
    "-s,--set-as-default\n"
    "  Saves the configuration choosen as the default on for future use.\n",
    std::numeric_limits<int>::max());

const auto color_error_message = fmt::format(
    "Error : the set of colors doesn't exists\n{}", color_flag_help_message);
const auto work_error_message =
    fmt::format("Error : the time for the work period is out of bounds\n{}",
                work_flag_help_message);
const auto break_error_message =
    fmt::format("Error : the time for the (small) break is out of bounds\n{}",
                break_flag_help_message);
const auto long_break_error_message =
    fmt::format("Error : the time for the long break is out of bounds\n{}",
                long_break_flag_help_message);

const auto help_message =
    fmt::format("Pomodoro options:\n\n{}\n{}\n{}\n{}", color_flag_help_message,
                work_flag_help_message, break_flag_help_message,
                long_break_flag_help_message, set_as_default_flag_help_message);

constexpr std::string_view work_timer = "Work";
constexpr std::string_view break_timer = "Break";

constexpr std::string_view current_timer =
    "Timer {} - Time remaining: {:%M:%S}";
constexpr std::string_view no_current_timer =
    "The Pomodoro has not been started.";
} // namespace pomodoro::strings
