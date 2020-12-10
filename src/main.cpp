#include "Pomodoro.hpp"
#include "color/Dictionary.hpp"
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

  const auto color_set = [&]() {
    auto color_set_selected{0};
    parser({"-c", "--color"}, 0) >> color_set_selected;

    if (color_set_selected >= pomodoro::color::dictionary.size()) {
      fmt::print(pomodoro::strings::color_error_message,
                 pomodoro::color::dictionary.size() - 1);
      fmt::print(
          "\nThe argument passed was {} whereas the accepted numbers are "
          "between 0 and {} included\n",
          color_set_selected, pomodoro::color::dictionary.size() - 1);
      std::terminate();
    }

    return pomodoro::color::dictionary[color_set_selected];
  }();

  const auto work_time = [&]() {
    auto work_time_selected{25};
    parser({"-w", "--work"}, 25) >> work_time_selected;
    if (work_time_selected == 0) {
      fmt::print(pomodoro::strings::work_error_message);
      fmt::print("\nYou cannot have a work time of 0 minutes\n");
      std::terminate();
    }
    return std::chrono::minutes(work_time_selected);
  }();

  const auto break_time = [&]() {
    auto break_time_selected{5};
    parser({"-b", "--break"}, 5) >> break_time_selected;
    if (break_time_selected == 0) {
      fmt::print(pomodoro::strings::break_error_message);
      fmt::print("\nYou cannot have a break time of 0 minutes\n");
      std::terminate();
    }
    return std::chrono::minutes(break_time_selected);
  }();

  const auto long_break_time = [&]() {
    auto long_break_time_selected{15};
    parser({"-lb", "--long-break"}, 15) >> long_break_time_selected;
    if (long_break_time_selected == 0) {
      fmt::print(pomodoro::strings::long_break_error_message);
      fmt::print("\nYou cannot have a long break time of 0 minutes\n");
      std::terminate();
    }
    return std::chrono::minutes(long_break_time_selected);
  }();

  Pomodoro pomodoro(color_set, work_time, break_time, long_break_time);
  pomodoro.run();

  while (pomodoro.isRunning()) {
    fmt::print("\r{}", pomodoro.getCurrentState());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return EXIT_SUCCESS;
}
