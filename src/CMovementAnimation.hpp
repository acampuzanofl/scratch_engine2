#ifndef CMovementAnimation_hpp
#define CMovementAnimation_hpp

#include <memory>

#include "CAnimation.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"

class CMovementAnimation : public Component {
 public:
  CMovementAnimation(Object* owner);
  void Awake() override;
  void Update(float deltaTime) override;

 private:
  std::shared_ptr<CVelocity> velocity;
  std::shared_ptr<CAnimation> animation;
};
#endif /* C_MovementAnimation_hpp */