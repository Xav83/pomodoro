#pragma once

#include "Timers.hpp"
#include <SFML/Audio.hpp>

class Pomodoro {
public:
  Pomodoro();
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  sf::Music start_break_sound, start_work_sound;
};
