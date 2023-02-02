#include "CKeyboardMovement.hpp"

#include <cassert>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "Component.hpp"
#include "Object.hpp"

CKeyboardMovement::CKeyboardMovement(Object* owner)
    : Component(owner), moveSpeed(200) {}

void CKeyboardMovement::Awake() {
  animation = owner->GetComponent<CAnimation>();
}
void CKeyboardMovement::SetInput(Input* input) { this->input = input; }

void CKeyboardMovement::SetMovementSpeed(int moveSpeed) {
  this->moveSpeed = moveSpeed;
}

void CKeyboardMovement::Update(float deltaTime) {
  assert(input != nullptr);

  // Update movement
  int xMove = 0;
  if (input->IsKeyPressed(Input::Key::Left)) {
    xMove = -moveSpeed;
  } else if (input->IsKeyPressed(Input::Key::Right)) {
    xMove = moveSpeed;
  }
  float xFrameMove = xMove * deltaTime;
  owner->transform->AddX(xFrameMove);

  /**
   * TODO: We are implementing this temproarly in the keyboard compononent
   * for testing GOAL: implement an animation state machine independent from
   * keyboard component
   */
  if (xMove == 0) {
    animation->SetAnimationState(AnimationState::Idle);
    /**
     * We are setting a flag to allow the collision system to know how to handle
     * collisions based on player movement.
     */
    owner->transform->SetIsMoving(false);
  } else {
    animation->SetAnimationState(AnimationState::Walk);
    owner->transform->SetIsMoving(true);
  }
}