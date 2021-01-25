#include "CommandLineParser.hpp"
#include "shared/utility/StringsDictionary.hpp"

pomodoro::CommandLineParser::Result
pomodoro::CommandLineParser::getConfigurationFromCommandLine(
    const argh::parser &parser,
    const pomodoro::Configuration &defaultConfiguration) {
  pomodoro::Configuration configuration = defaultConfiguration;
  auto color_set_selected{0};
  if (parser({"-c", "--color"}) >> color_set_selected) {
    if (color_set_selected < pomodoro::numbers::color_id_min ||
        color_set_selected >= pomodoro::numbers::number_of_colors) {
      return {defaultConfiguration, false,
              fmt::format("{}\nThe argument passed was {} whereas the accepted "
                          "numbers are between {} and {} included\n",
                          pomodoro::strings::color_error_message,
                          color_set_selected, pomodoro::numbers::color_id_min,
                          pomodoro::numbers::number_of_colors - 1)};
    }
    configuration.setColorId(
        static_cast<pomodoro::color::Id>(color_set_selected));
  }

  auto work_time_selected{pomodoro::numbers::default_work_time};
  if (parser({"-w", "--work"}) >> work_time_selected) {
    if (work_time_selected == 0) {
      return {defaultConfiguration, false,
              fmt::format("{}\nYou cannot have a work time of 0 minutes\n",
                          pomodoro::strings::work_error_message)};
    }
    configuration.setWorkTime(std::chrono::minutes(work_time_selected));
  }

  auto break_time_selected{pomodoro::numbers::default_break_time};
  if (parser({"-b", "--break"}) >> break_time_selected) {
    if (break_time_selected == 0) {
      return {defaultConfiguration, false,
              fmt::format("{}\nYou cannot have a break time of 0 minutes\n",
                          pomodoro::strings::break_error_message)};
    }
    configuration.setBreakTime(std::chrono::minutes(break_time_selected));
  }

  auto long_break_time_selected{pomodoro::numbers::default_long_break_time};
  if (parser({"-lb", "--long-break"}) >> long_break_time_selected) {
    if (long_break_time_selected == 0) {
      return {
          defaultConfiguration, false,
          fmt::format("{}\nYou cannot have a long break time of 0 minutes\n",
                      pomodoro::strings::long_break_error_message)};
    }
    configuration.setLongBreakTime(
        std::chrono::minutes(long_break_time_selected));
  }

  return {configuration, true, fmt::format("Success")};
}
