#include "Debug.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<sf::RectangleShape> Debug::rects = {};
std::vector<std::array<sf::Vertex, 2>> Debug::lines = {};

void Debug::Draw(Window& window) {
  for (auto& r : rects) {
    window.Draw(r);
  }
  rects.clear();

  for (auto& l : lines) {
    sf::Vertex line[2] = {l.at(0), l.at(1)};
    window.Draw(line, 2, sf::PrimitiveType::Lines);
  }
  lines.clear();
}

void Debug::DrawRect(const sf::FloatRect& rect, sf::Color color) {
  sf::Vector2f size(rect.size);
  sf::Vector2f pos(rect.position);
  sf::RectangleShape shape(size);
  shape.setPosition(pos);
  shape.setOutlineColor(color);
  shape.setOutlineThickness(3.f);
  shape.setFillColor(sf::Color::Transparent);
  rects.push_back(shape);
}

// this method allows you to print rects centered around an origin
void Debug::DrawRect(const sf::FloatRect& rect, const sf::Vector2f origin,
                     sf::Color color) {
  sf::Vector2f size(rect.size);
  sf::Vector2f pos(rect.position.x - origin.x, rect.position.y - origin.y);
  sf::RectangleShape shape(size);
  shape.setPosition(pos);
  shape.setOutlineColor(color);
  shape.setOutlineThickness(3.f);
  shape.setFillColor(sf::Color::Transparent);
  rects.push_back(shape);
}

void Debug::DrawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                     sf::Color colour) {
  lines.push_back({from, colour});
  lines.push_back({to, colour});

}

void Debug::Log(const std::string& msg) { std::cout << msg << std::endl; }
