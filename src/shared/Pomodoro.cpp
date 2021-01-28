#include "Pomodoro.hpp"
#include "Configuration.hpp"
#include "utility/FilesDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <cassert>
#include <filesystem>
#include <fmt/core.h>

Pomodoro::Pomodoro(const pomodoro::Configuration &configuration,
                   std::function<void()> work_timer_callback,
                   std::function<void()> break_timer_callback,
                   std::function<void()> long_break_timer_callback) {
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

const pomodoro::Timer &Pomodoro::getCurrentTimer() const {
  if (!isRunning()) {
    return timers.getTimer(0);
  }
  const auto it =
      std::find_if(timers.cbegin(), timers.cend(),
                   [](const auto &timer) { return timer.isRunning(); });
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(it != timers.cend());

  return *it;
}
