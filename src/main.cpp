#include "ConfigurationFile.hpp"
#include "Pomodoro.hpp"
#include "color/Dictionary.hpp"
#include "utility/FilesDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <argh.h>
#include <thread>
#include <utility>

int main(int, char *argv[]) {
  argh::parser parser(argv);

  if (parser[{"-h", "--help"}]) {
    fmt::print(pomodoro::strings::help_message);
    return EXIT_SUCCESS;
  }

  pomodoro::ConfigurationFile configurationFile(pomodoro::files::configuration);
  auto configuration = [&configurationFile]() {
    if (std::filesystem::exists(pomodoro::files::configuration)) {
      return configurationFile.load();
    }
    return pomodoro::Configuration();
  }();

  auto color_set_selected{0};
  if (parser({"-c", "--color"}) >> color_set_selected) {
    if (color_set_selected >= pomodoro::numbers::number_of_colors) {
      fmt::print(pomodoro::strings::color_error_message);
      fmt::print(
          "\nThe argument passed was {} whereas the accepted numbers are "
          "between 0 and {} included\n",
          color_set_selected, pomodoro::numbers::number_of_colors - 1);
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

  if (parser[{"-s", "--set-as-default"}]) {
    configurationFile.save(configuration);
  }

  Pomodoro pomodoro(configuration);
  pomodoro.run();

  while (pomodoro.isRunning()) {
    fmt::print("\r{}", pomodoro.getCurrentState());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return EXIT_SUCCESS;
}
