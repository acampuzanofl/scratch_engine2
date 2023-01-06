#ifndef CKEYBOARDMOVEMENT_HPP
#define CKEYBOARDMOVEMENT_HPP

#include "Component.hpp"
#include "Input.hpp"

class CKeyboardMovement : public Component {
 public:
  CKeyboardMovement(Object* owner);
  void SetInput(Input* input);
  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

 private:
  int moveSpeed;
  Input* input;
};

#endif