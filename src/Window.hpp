#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/System/Vector2.hpp>

#include "SFML/Graphics.hpp"

class Window {
 public:
  Window(const std::string& windowName);

  void HandleEvents();
  void Clear();
  void Draw(const sf::Drawable& drawable);
  void Update();
  bool IsOpen() const;
  sf::Vector2u GetCenter() const;

 private:
  sf::RenderWindow window;
};

#endif