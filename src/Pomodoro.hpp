#pragma once

#include "ColorSet.hpp"
#include "Timers.hpp"
#include <SFML/Audio.hpp>
#include <utility>

class Pomodoro {
public:
  Pomodoro(pomodoro::ColorSet colors);
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  sf::Music start_break_sound, start_work_sound;
  pomodoro::ColorSet colors;
};
