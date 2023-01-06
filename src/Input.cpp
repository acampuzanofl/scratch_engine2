#include "Input.hpp"
#include <SFML/Window/Keyboard.hpp>

void Input::PollKey() {
    previousFrameKeys.SetMask(currentFrameKeys);
    currentFrameKeys.SetBit((int)Key::Left, sf::Keyboard::isKeyPressed(sf::Keyboard::A));
    currentFrameKeys.SetBit((int)Key::Right, sf::Keyboard::isKeyPressed(sf::Keyboard::D));
    currentFrameKeys.SetBit((int)Key::Up, sf::Keyboard::isKeyPressed(sf::Keyboard::S));
    currentFrameKeys.SetBit((int)Key::Down, sf::Keyboard::isKeyPressed(sf::Keyboard::W));
}

bool Input::IsKeyPressed(Key keycode) {
    return currentFrameKeys.GetBit((int) keycode);
}

bool Input::IsKeyDown(Key keycode) {
    bool previousFrame = previousFrameKeys.GetBit((int) keycode);
    bool currentFrame = currentFrameKeys.GetBit((int) keycode);
    return currentFrame && !previousFrame;
}

bool Input::IsKeyUp(Key keycode) {
    bool previousFrame = previousFrameKeys.GetBit((int) keycode);
    bool currentFrame = currentFrameKeys.GetBit((int) keycode);
    return !currentFrame && previousFrame;
}