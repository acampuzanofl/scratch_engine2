#ifndef canimation_hpp
#define canimation_hpp

#include <map>
#include <memory>
#include <utility>

#include "Animation.hpp"
#include "CSprite.hpp"
#include "Component.hpp"

// CAnimation Is responsible for setting and updating animation for the owner
// The owner must have a CSprite
enum class AnimationState { None, Idle, Walk, A, B, C, D };

class CAnimation : public Component {
 public:
  CAnimation(Object* owner);
  void Awake() override;
  void Update(float deltaTime) override;
  void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);
  void SetAnimationState(AnimationState state);
  const AnimationState& GetCurrentAnimationState() const;
  const std::shared_ptr<Animation>& GetCurrentAnimation() const;
  void SetCurrentFrame();

 private:
  std::shared_ptr<CSprite> sprite;
  std::map<AnimationState, std::shared_ptr<Animation>> animations;
  std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};

#endif
