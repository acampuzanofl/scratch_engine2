#ifndef debug_hpp
#define debug_hpp

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <vector>

#include "Window.hpp"

class Debug {
 public:
  static void Draw(Window& window);
  static void DrawRect(const sf::FloatRect& rect,
                       sf::Color color = sf::Color::Red);
  static void DrawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                       sf::Color color = sf::Color::Red);
  static void Log(const std::string& msg);

 private:
  static std::vector<std::array<sf::Vertex, 2>> lines;
  static std::vector<sf::RectangleShape> rects;
};

#endif