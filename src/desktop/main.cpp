#include "Fonts.hpp"
#include "shared/Pomodoro.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Pomodoro");
  sf::Font font;
  font.loadFromFile(pomodoro::fonts::main.string());

  sf::Text text;
  text.setString("Hello world");
  text.setFont(font);
  text.setCharacterSize(24);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(text);
    window.display();
  }

  return 0;
}
