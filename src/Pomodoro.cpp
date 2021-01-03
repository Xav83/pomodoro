#include "Pomodoro.hpp"
#include "Configuration.hpp"
#include "utility/FilesDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <cassert>
#include <filesystem>
#include <fmt/chrono.h>
#include <fmt/core.h>

Pomodoro::Pomodoro(const pomodoro::Configuration &configuration)
    : colors(configuration.getColors()) {
  assert(std::filesystem::exists(pomodoro::files::sounds::start_break));
  assert(std::filesystem::exists(pomodoro::files::sounds::start_work));
  start_break_sound.openFromFile(pomodoro::files::sounds::start_break.string());
  start_work_sound.openFromFile(pomodoro::files::sounds::start_work.string());

  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(1).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(2).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(3).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(4).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(5).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getBreakTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(6).start();
                      });
  timers.emplaceTimer(pomodoro::strings::work_timer,
                      configuration.getWorkTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
                        timers.getTimer(7).start();
                      });
  timers.emplaceTimer(pomodoro::strings::break_timer,
                      configuration.getLongBreakTime(), [this]() {
                        start_break_sound.stop();
                        start_break_sound.play();
                        fmt::print("\n");
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
  assert(it != timers.cend());

  const auto name = [&it, this]() {
    if (it->getName() == pomodoro::strings::work_timer) {
      return fmt::format(fg(colors.work_color) | fmt::emphasis::bold,
                         it->getName().data());
    }
    return fmt::format(fg(colors.break_color) | fmt::emphasis::bold,
                       it->getName().data());
  }();

  return fmt::format(pomodoro::strings::current_timer, name,
                     it->getRemainingTime());
}
