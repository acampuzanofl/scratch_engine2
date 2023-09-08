#include "CKeyboardAttack.hpp"

#include "Object.hpp"
CKeyboardAttack::CKeyboardAttack(Object* owner) : Component(owner) {}
void CKeyboardAttack::Awake() { animation = owner->GetComponent<CAnimation>(); }
void CKeyboardAttack::Update(float deltaTime) {
  if (input->IsKeyPressed(Input::Key::B)) {
    animation->SetAnimationState(AnimationState::B);
  }
}
void CKeyboardAttack::SetInput(Input* input) { this->input = input; }