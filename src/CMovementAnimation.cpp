#include "CMovementAnimation.hpp"
#include "Object.hpp"

CMovementAnimation::CMovementAnimation(Object *owner) : Component(owner) {}
void CMovementAnimation::Awake() {
  velocity = owner->GetComponent<CVelocity>();
  animation = owner->GetComponent<CAnimation>();
}
void CMovementAnimation::Update(float deltaTime) {
  if (animation->GetCurrentAnimationState() != AnimationState::B) {
    const sf::Vector2f& currentVel = velocity->Get();
    if (currentVel.x != 0.f) {
      animation->SetAnimationState(AnimationState::Walk);
    } else {
      animation->SetAnimationState(AnimationState::Idle);
    }
  }
}
