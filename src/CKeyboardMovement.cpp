#include "CKeyboardMovement.hpp"

#include <SFML/System/Vector2.hpp>
#include <cassert>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "Component.hpp"
#include "Object.hpp"

CKeyboardMovement::CKeyboardMovement(Object* owner) : Component(owner) {}
void CKeyboardMovement::Awake() {
  animation = owner->GetComponent<CAnimation>();
}
void CKeyboardMovement::SetInput(Input* input) { this->input = input; }
void CKeyboardMovement::Update(float deltaTime) {
  assert(input != nullptr);

  // Update movement
  if (input->IsKeyPressed(Input::Key::Left)) {
    /**
     * movement speed should be a property of the transform object
     * we are hardcoding it for now do to ease of use
     * TODO: need to change the im
     */

    owner->transform->SetVelocity(sf::Vector2f(-200, 0));
  } else if (input->IsKeyPressed(Input::Key::Right)) {
    owner->transform->SetVelocity(sf::Vector2f(200, 0));
  }

  /**
   * TODO: We are implementing this temproarly in the keyboard compononent
   * for testing implement an animation state machine independent from
   * keyboard component
   */
  if (owner->transform->GetVelocity().x == 0) {
    animation->SetAnimationState(AnimationState::Idle);
  } else {
    animation->SetAnimationState(AnimationState::Walk);
  }
}