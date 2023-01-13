#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>

#include "Bitmask.hpp"

class Input {
 public:
  enum class Key { None, Left, Right, Up, Down, Esc };
  void PollKey();
  bool IsKeyPressed(Key keycode);
  bool IsKeyDown(Key keycode);
  bool IsKeyUp(Key keycode);

 private:
  Bitmask currentFrameKeys;
  Bitmask previousFrameKeys;
};

#endif