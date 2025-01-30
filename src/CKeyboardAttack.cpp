#include "CKeyboardAttack.hpp"

#include "CAnimation.hpp"
#include "Object.hpp"
CKeyboardAttack::CKeyboardAttack(Object* owner) : Component(owner) {}
void CKeyboardAttack::Awake() {
  animation = owner->GetComponent<CAnimation>();
  /**
   * TODO
   * This is a temporary solution to restoring idle at the end
   * of a oneshot animation. The proper solution would be to implement
   * an animation state machine. Im suprised this worked first try though
   */
  auto battack = animation->GetAnimationByState(AnimationState::B);
  battack->AddFrameCallback(battack->GetAnimationSize() - 1, [this]() {
    animation->SetAnimationState(AnimationState::Idle);
  });

  //   auto dattack = animation->GetAnimationByState(AnimationState::D);
  // dattack->AddFrameCallback(dattack->GetAnimationSize() - 1, [this]() {
  //   animation->SetAnimationState(AnimationState::Idle);
  // });
}
void CKeyboardAttack::Update(float deltaTime) {
  if (owner->context->input->IsKeyPressed(Input::Key::B)) {
    animation->SetAnimationState(AnimationState::B);
  }
  //   if (owner->context->input->IsKeyPressed(Input::Key::D)) {
  //   animation->SetAnimationState(AnimationState::D);
  // }
}