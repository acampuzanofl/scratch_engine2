#ifndef CKEYBOARDMOVEMENT_HPP
#define CKEYBOARDMOVEMENT_HPP

#include <memory>

#include "CVelocity.hpp"
#include "Component.hpp"
#include "Input.hpp"

class CKeyboardMovement : public Component {
 public:
  CKeyboardMovement(Object* owner);
  void Awake() override;
  void SetInput(Input* input);
  void SetMovementSpeed(float moveSpeed);
  void Update(float deltaTime) override;

 private:
  float moveSpeed;
  Input* input;
  std::shared_ptr<CVelocity> velocity;
};

#endif