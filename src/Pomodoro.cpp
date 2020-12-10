#include "Pomodoro.hpp"
#include "utility/SoundsDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <cassert>
#include <filesystem>
#include <fmt/chrono.h>
#include <fmt/core.h>

Pomodoro::Pomodoro(pomodoro::color::Set colors_)
    : Pomodoro(colors_, std::chrono::minutes(25), std::chrono::minutes(5),
               std::chrono::minutes(15)) {}

Pomodoro::Pomodoro(pomodoro::color::Set colors_, std::chrono::minutes work_time,
                   std::chrono::minutes break_time,
                   std::chrono::minutes long_break_time)
    : colors(colors_) {
  assert(std::filesystem::exists(pomodoro::sounds::file::start_break));
  assert(std::filesystem::exists(pomodoro::sounds::file::start_work));
  start_break_sound.openFromFile(pomodoro::sounds::file::start_break.string());
  start_work_sound.openFromFile(pomodoro::sounds::file::start_work.string());

  timers.emplaceTimer(pomodoro::strings::work_timer, work_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(1).start();
  });
  timers.emplaceTimer(pomodoro::strings::break_timer, break_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(2).start();
  });
  timers.emplaceTimer(pomodoro::strings::work_timer, work_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(3).start();
  });
  timers.emplaceTimer(pomodoro::strings::break_timer, break_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(4).start();
  });
  timers.emplaceTimer(pomodoro::strings::work_timer, work_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(5).start();
  });
  timers.emplaceTimer(pomodoro::strings::break_timer, break_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(6).start();
  });
  timers.emplaceTimer(pomodoro::strings::work_timer, work_time, [this]() {
    start_break_sound.stop();
    start_break_sound.play();
    fmt::print("\n");
    timers.getTimer(7).start();
  });
  timers.emplaceTimer(pomodoro::strings::break_timer, long_break_time,
                      [this]() {
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
