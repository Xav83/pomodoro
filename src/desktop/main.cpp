#include <SFML/Window.hpp>
#include "shared/Pomodoro.hpp"

int main() {
  sf::Window window(sf::VideoMode(800, 600), "Pomodoro");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  return 0;
}
