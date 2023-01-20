#include "Window.hpp"

#include <SFML/System/Vector2.hpp>

Window::Window(const std::string& windowName)
    : window(sf::VideoMode(800, 600), windowName, sf::Style::Titlebar) {
  window.setVerticalSyncEnabled(true);
}

void Window::HandleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
      window.close();
    }
  }
}

void Window::Clear() { window.clear(sf::Color::White); }

void Window::Draw(const sf::Drawable& drawable) { window.draw(drawable); }

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount,
                  sf::PrimitiveType type) {
  window.draw(vertices, vertexCount, type);
}

void Window::Update() { window.display(); }

bool Window::IsOpen() const { return window.isOpen(); }

sf::Vector2u Window::GetCenter() const {
  sf::Vector2u size = window.getSize();
  return sf::Vector2u(size.x / 2, size.y / 2);
}