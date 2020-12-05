#pragma once

#include "ColorSet.hpp"
#include "Timers.hpp"
#include <SFML/Audio.hpp>
#include <utility>

class Pomodoro {
public:
  Pomodoro(pomodoro::ColorSet colors);
  Pomodoro(pomodoro::ColorSet colors, std::chrono::minutes work_time,
           std::chrono::minutes break_time,
           std::chrono::minutes long_break_time);
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  sf::Music start_break_sound, start_work_sound;
  pomodoro::ColorSet colors;
};
