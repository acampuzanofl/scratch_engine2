#ifndef ckeyboardattack_hpp
#define ckeyboardattack_hpp
#include "CAnimation.hpp"
#include "Component.hpp"
#include "Input.hpp"
class CKeyboardAttack : public Component {
 public:
  CKeyboardAttack(Object* owner);
  void Awake() override;
  void Update(float deltaTime) override;
  void SetInput(Input* input);

 private:
  std::shared_ptr<CAnimation> animation;
  Input* input;
};
#endif /* ckeyboardattack_hpp */