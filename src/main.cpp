#include "Colors.hpp"
#include "Pomodoro.hpp"
#include <argh.h>
#include <thread>
#include <utility>

int main(int, char *argv[]) {
  argh::parser parser(argv);

  const auto color_set = [&]() {
    auto color_set_selected{0};
    parser({"-c", "--color"}, 0) >> color_set_selected;

    if (color_set_selected >= pomodoro::colors.size()) {
      fmt::print("Error : [-c|--color]=[0-{}]\n", pomodoro::colors.size() - 1);
      fmt::print("The argument passed was {} whereas the accepted numbers are "
                 "between 0 and {} included\n",
                 color_set_selected, pomodoro::colors.size() - 1);
      std::terminate();
    }

    return pomodoro::colors[color_set_selected];
  }();

  Pomodoro pomodoro(color_set);
  pomodoro.run();

  while (pomodoro.isRunning()) {
    fmt::print("\r{}", pomodoro.getCurrentState());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}
