#include "CommandLineParser.hpp"
#include "utility/StringsDictionary.hpp"

pomodoro::Configuration CommandLineParser::getConfigurationFromCommandLine(
    argh::parser parser, const pomodoro::Configuration &defaultConfiguration) {
  pomodoro::Configuration configuration = defaultConfiguration;
  auto color_set_selected{0};
  if (parser({"-c", "--color"}) >> color_set_selected) {
    if (color_set_selected < pomodoro::numbers::color_id_min ||
        color_set_selected >= pomodoro::numbers::number_of_colors) {
      fmt::print(pomodoro::strings::color_error_message);
      fmt::print(
          "\nThe argument passed was {} whereas the accepted numbers are "
          "between {} and {} included\n",
          color_set_selected, pomodoro::numbers::color_id_min,
          pomodoro::numbers::number_of_colors - 1);
      std::terminate();
    }
    configuration.setColorId(
        static_cast<pomodoro::color::Id>(color_set_selected));
  }

  auto work_time_selected{pomodoro::numbers::default_work_time};
  if (parser({"-w", "--work"}) >> work_time_selected) {
    if (work_time_selected == 0) {
      fmt::print(pomodoro::strings::work_error_message);
      fmt::print("\nYou cannot have a work time of 0 minutes\n");
      std::terminate();
    }
    configuration.setWorkTime(std::chrono::minutes(work_time_selected));
  }

  auto break_time_selected{pomodoro::numbers::default_break_time};
  if (parser({"-b", "--break"}) >> break_time_selected) {
    if (break_time_selected == 0) {
      fmt::print(pomodoro::strings::break_error_message);
      fmt::print("\nYou cannot have a break time of 0 minutes\n");
      std::terminate();
    }
    configuration.setBreakTime(std::chrono::minutes(break_time_selected));
  }

  auto long_break_time_selected{pomodoro::numbers::default_long_break_time};
  if (parser({"-lb", "--long-break"}) >> long_break_time_selected) {
    if (long_break_time_selected == 0) {
      fmt::print(pomodoro::strings::long_break_error_message);
      fmt::print("\nYou cannot have a long break time of 0 minutes\n");
      std::terminate();
    }
    configuration.setLongBreakTime(
        std::chrono::minutes(long_break_time_selected));
  }

  return configuration;
}
