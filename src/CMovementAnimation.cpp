#include "CMovementAnimation.hpp"

#include "CKeyboardMovement.hpp"
#include "Object.hpp"
CMovementAnimation::CMovementAnimation(Object* owner) : Component(owner) {}
void CMovementAnimation::Awake() {
  velocity = owner->GetComponent<CVelocity>();
  animation = owner->GetComponent<CAnimation>();
  keyboard = owner->GetComponent<CKeyboardMovement>();
}
void CMovementAnimation::Update(float deltaTime) {
  if (animation->GetCurrentAnimationState() != AnimationState::B) {
    auto input = keyboard->GetInput();
    if (input->IsKeyPressed(Input::Key::Left) ||
        input->IsKeyPressed(Input::Key::Right)) {
      animation->SetAnimationState(AnimationState::Walk);
    } else {
      animation->SetAnimationState(AnimationState::Idle);
    }
  }
}