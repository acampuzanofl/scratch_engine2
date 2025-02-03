#ifndef debug_hpp
#define debug_hpp

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <vector>
#include <iostream>

#include "Window.hpp"

#define ERROR(format, ...) Debug::Error(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define DEBUG(format, ...) Debug::Log(__FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)


class Debug {
 public:
  static void Draw(Window& window);
  static void DrawRect(const sf::FloatRect& rect,
                       sf::Color color = sf::Color::Red);
  // this method allows you to print rects centered around an origin
  static void DrawRect(const sf::FloatRect& rect, const sf::Vector2f origin,
                       sf::Color color = sf::Color::Red);
  static void DrawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                       sf::Color color = sf::Color::Red);
  static void Log(const std::string& msg);
  static void Error(const std::string& msg);

  // This template allows for variadic arguments.
  // we use this template to allow us to make a wrapper for printf
  template <typename... Args>
  static void Log(const std::string& msg, Args... args) {
    const std::string logColor = "\033[38;5;210m";
    const std::string resetColor = "\033[0m";
    std::printf(( logColor + "[DEBUG] " + msg + resetColor + "\n" ).c_str(), args...);
  }

    template <typename... Args>
    static void Error(const std::string& file, int line, const std::string& function, const std::string& formatStr, Args&&... args) {
        const std::string redColor = "\033[31m";
        const std::string resetColor = "\033[0m";

        // Format the message
        std::string formattedMessage = std::vformat(formatStr, std::make_format_args(std::forward<Args>(args)...));

        // Print the error with file and line information
        std::cerr << redColor << "[ERROR] " << file << ":" << line << ": " << function << "() "
                  << formattedMessage << resetColor << std::endl;
    }
 private:
  static std::vector<std::array<sf::Vertex, 2>> lines;
  static std::vector<sf::RectangleShape> rects;
};


#endif