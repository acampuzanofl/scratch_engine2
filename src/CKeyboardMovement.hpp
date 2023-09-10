#ifndef CKEYBOARDMOVEMENT_HPP
#define CKEYBOARDMOVEMENT_HPP

#include <memory>

#include "CAnimation.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"
#include "Input.hpp"

class CKeyboardMovement : public Component {
 public:
  CKeyboardMovement(Object* owner);
  void Awake() override;
  void SetInput(Input* input);
  Input* GetInput();
  void SetMovementSpeed(float moveSpeed);
  void Update(float deltaTime) override;

 private:
  float moveSpeed;
  Input* input;
  std::shared_ptr<CVelocity> velocity;
  std::shared_ptr<CAnimation> animation;
};

#endif