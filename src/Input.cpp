#include "Input.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <memory>

void Input::PollKey() {
  previousFrameKeys.SetMask(currentFrameKeys);
  for (auto& key : *keymap) {
    currentFrameKeys.SetBit((int)key.first,
                            sf::Keyboard::isKeyPressed(key.second));
  }
}

bool Input::IsKeyPressed(Key keycode) {
  return currentFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyDown(Key keycode) {
  bool previousFrame = previousFrameKeys.GetBit((int)keycode);
  bool currentFrame = currentFrameKeys.GetBit((int)keycode);
  return currentFrame && !previousFrame;
}

bool Input::IsKeyUp(Key keycode) {
  bool previousFrame = previousFrameKeys.GetBit((int)keycode);
  bool currentFrame = currentFrameKeys.GetBit((int)keycode);
  return !currentFrame && previousFrame;
}

void Input::SubscribeToKeys(KeyMap& keymap) {
  this->keymap = std::make_unique<KeyMap>(keymap);
}