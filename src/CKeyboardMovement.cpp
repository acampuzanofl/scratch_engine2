#include "CKeyboardMovement.hpp"

#include <SFML/System/Vector2.hpp>
#include <cassert>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"
#include "Debug.hpp"
#include "Input.hpp"
#include "Object.hpp"

/**
 * TODO make a new Ckeyboard component that acts as a parent to all
 * children that inherits the Ckeyboard component
 * this way i can make multiple keyboard dependent classes where
 * i wouldnt need to pass an input to all of them
 */
CKeyboardMovement::CKeyboardMovement(Object* owner)
    : Component(owner), moveSpeed(300.f) {}
void CKeyboardMovement::Awake() { velocity = owner->GetComponent<CVelocity>(); }
void CKeyboardMovement::SetInput(Input* input) { this->input = input; }
Input* CKeyboardMovement::GetInput() { return input; }
void CKeyboardMovement::SetMovementSpeed(float moveSpeed) {
  this->moveSpeed = moveSpeed;
}
void CKeyboardMovement::Update(float deltaTime) {
  assert(input != nullptr);

  // Update movement
  if (input->IsKeyPressed(Input::Key::Left)) {
    velocity->Set(sf::Vector2f(-200, 0));
  } else if (input->IsKeyPressed(Input::Key::Right)) {
    velocity->Set(sf::Vector2f(200, 0));
  }
}