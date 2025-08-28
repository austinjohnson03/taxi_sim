#include <SFML/Graphics.hpp>
#include "car.h"
#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  Graph city;

  sf::RenderWindow window(sf::VideoMode(1280, 720), "Car Demo");
  window.setFramerateLimit(144);

  sf::Font font;
  if (!font.loadFromFile("Roboto-Medium.ttf")) {
    std::cout << "Error loading font from file." << std::endl;
    return -1;
  }

  sf::Text info_text;
  info_text.setFont(font);
  info_text.setCharacterSize(20);
  info_text.setFillColor(sf::Color::White);
  info_text.setPosition(10.f, 10.f);

  Car car(400.f, 300.f);
  car.accelerate(100.f);
  car.turn(0.8f);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed)
        window.close();
    }

    float dt = clock.restart().asSeconds();
    car.update(dt, window);

    window.clear(sf::Color(17, 64, 0));
    city.draw(window);
    car.draw(window);
    info_text.setString(
        "Velocity: " + std::to_string(car.get_velocity()) + "\n" +
        "Acceleration: " + std::to_string(car.get_accel_input()) + "\n" +
        "Steer Angle: " + std::to_string(car.get_steer_angle())
        );
    window.draw(info_text);
    window.display();

  }
}
