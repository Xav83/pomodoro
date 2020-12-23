#pragma once

#include "Timers.hpp"
#include "color/Set.hpp"
#include <SFML/Audio.hpp>
#include <utility>

namespace pomodoro {
class Configuration;
}

class Pomodoro {
public:
  Pomodoro(const pomodoro::Configuration &configuration);
  ~Pomodoro();

  void run();

  bool isRunning() const;

  std::string getCurrentState() const;

private:
  pomodoro::Timers timers;
  sf::Music start_break_sound, start_work_sound;
  pomodoro::color::Set colors;
};
