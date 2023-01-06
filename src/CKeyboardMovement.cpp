#include "CKeyboardMovement.hpp"

#include "Component.hpp"
#include "Object.hpp"

CKeyboardMovement::CKeyboardMovement(Object* owner)
    : Component(owner), moveSpeed(200) {}

void CKeyboardMovement::SetInput(Input* input) { this->input = input; }

void CKeyboardMovement::SetMovementSpeed(int moveSpeed) {
  this->moveSpeed = moveSpeed;
}

void CKeyboardMovement::Update(float deltaTime) {
  if (input == nullptr) {
    return;
  }
  // Update movement
  int xMove = 0;
  if (input->IsKeyPressed(Input::Key::Left)) {
    xMove = -moveSpeed;
  } else if (input->IsKeyPressed(Input::Key::Right)) {
    xMove = moveSpeed;
  }
  float xFrameMove = xMove * deltaTime;
  owner->transform->AddX(xFrameMove);
}