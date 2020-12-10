#pragma once

#include "Timers.hpp"
#include "color/Set.hpp"
#include <SFML/Audio.hpp>
#include <utility>

class Pomodoro {
public:
  explicit Pomodoro(pomodoro::color::Set colors_);
  Pomodoro(pomodoro::color::Set colors_, std::chrono::minutes work_time,
           std::chrono::minutes break_time,
           std::chrono::minutes long_break_time);
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  sf::Music start_break_sound, start_work_sound;
  pomodoro::color::Set colors;
};
