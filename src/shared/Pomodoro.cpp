#include "Pomodoro.hpp"
#include "Configuration.hpp"
#include "utility/FilesDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <cassert>
#include <filesystem>
#include <fmt/chrono.h>
#include <fmt/core.h>

Pomodoro::Pomodoro(const pomodoro::Configuration &configuration,
                   std::function<void()> work_timer_callback,
                   std::function<void()> break_timer_callback,
                   std::function<void()> long_break_timer_callback)
    : color_id(configuration.getColorId()) {
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(),
                      [this, callback = std::move(work_timer_callback)]() {
                        callback();
                        timers.getTimer(1).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(),
                      [this, callback = std::move(break_timer_callback)]() {
                        callback();
                        timers.getTimer(2).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(),
                      [this, callback = std::move(work_timer_callback)]() {
                        callback();
                        timers.getTimer(3).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(),
                      [this, callback = std::move(break_timer_callback)]() {
                        callback();
                        timers.getTimer(4).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(),
                      [this, callback = std::move(work_timer_callback)]() {
                        callback();
                        timers.getTimer(5).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(),
                      [this, callback = std::move(break_timer_callback)]() {
                        callback();
                        timers.getTimer(6).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(),
                      [this, callback = std::move(work_timer_callback)]() {
                        callback();
                        timers.getTimer(7).start();
                      });
  timers.emplaceTimer(
      pomodoro::strings::break_timer, configuration.getLongBreakTime(),
      [this, callback = std::move(long_break_timer_callback)]() {
        callback();
        timers.getTimer(0).start();
      });
}

Pomodoro::~Pomodoro() = default;

void Pomodoro::run() { timers.getTimer(0).start(); }

bool Pomodoro::isRunning() const { return timers.hasOneTimerRunning(); }

std::string Pomodoro::getCurrentState() const {
  if (!isRunning()) {
    return pomodoro::strings::no_current_timer.data();
  }
  const auto it =
      std::find_if(timers.cbegin(), timers.cend(),
                   [](const auto &timer) { return timer.isRunning(); });
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(it != timers.cend());

  const auto name = [&it, this]() {
    if (color_id != pomodoro::color::Id::no_color) {
      auto color_set =
          pomodoro::color::dictionary.at(static_cast<size_t>(color_id));
      if (it->getName() == pomodoro::strings::work_timer) {
        return fmt::format(fg(color_set.work_color), it->getName().data());
      }
      return fmt::format(fg(color_set.break_color), it->getName().data());
    }
    return fmt::format(it->getName().data());
  }();

  return fmt::format(pomodoro::strings::current_timer, name,
                     it->getRemainingTime());
}
