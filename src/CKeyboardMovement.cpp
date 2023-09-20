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
void CKeyboardMovement::Awake() {
  velocity = owner->GetComponent<CVelocity>();
  animation = owner->GetComponent<CAnimation>();
}
void CKeyboardMovement::SetMovementSpeed(float moveSpeed) {
  this->moveSpeed = moveSpeed;
}
void CKeyboardMovement::Update(float deltaTime) {
  assert(owner->context->input != nullptr);

  /**
   * TODO
   * This is a temporary solution to get the "feeling" of the movement
   * and animation correct. But this is not a good of implementing
   * The keyboard componenent should not interact with th animatino component
   * The keyboard componoent should know nothing about what animation is running
   */
  if (animation->GetCurrentAnimationState() == AnimationState::B) {
    return;
  }

  // Update movement
  if (owner->context->input->IsKeyPressed(Input::Key::Left)) {
    velocity->Set(sf::Vector2f(-200, 0));
  } else if (owner->context->input->IsKeyPressed(Input::Key::Right)) {
    velocity->Set(sf::Vector2f(200, 0));
  }
}