#ifndef C_Direction_hpp
#define C_Direction_hpp

#include "Animation.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"

enum class FacingDirection { None, Left, Right };

class CDirection : public Component {
 public:
  CDirection(Object* owner);

  void Awake() override;

  FacingDirection Get();

 private:
  std::shared_ptr<CVelocity> velocity;
  FacingDirection currentDir;
};

#endif /* C_Direction_hpp */