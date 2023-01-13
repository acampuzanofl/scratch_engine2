#ifndef CKEYBOARDMOVEMENT_HPP
#define CKEYBOARDMOVEMENT_HPP

#include <memory>

#include "CAnimation.hpp"
#include "Component.hpp"
#include "Input.hpp"

class CKeyboardMovement : public Component {
 public:
  CKeyboardMovement(Object* owner);
  void Awake() override;
  void SetInput(Input* input);
  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

 private:
  int moveSpeed;
  Input* input;
  // TODO: ckeyboard should not know anything about animation, we are doing this
  // as a temp solution for controlling animation direction ultimate goal is to
  // have direction automatically adjust to the direction of the opponent.
  std::shared_ptr<CAnimation> animation;
};

#endif