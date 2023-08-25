#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <memory>
#include <vector>

#include "Bitmask.hpp"

class Input {
 public:
  enum class Key { None, Left, Right, Up, Down, Exit, Zoomin, Zoomout };
  typedef std::map<Key, sf::Keyboard::Key> KeyMap;

  void PollKey();
  bool IsKeyPressed(Key keycode);
  bool IsKeyDown(Key keycode);
  bool IsKeyUp(Key keycode);
  void SubscribeToKeys(KeyMap& keyMap);

 private:
  Bitmask currentFrameKeys;
  Bitmask previousFrameKeys;
  std::unique_ptr<KeyMap> keymap;
};

#endif