#ifndef canimation_hpp
#define canimation_hpp

#include <map>
#include <memory>
#include <utility>

#include "Animation.hpp"
#include "CSprite.hpp"
#include "Component.hpp"

enum class AnimationState { None, Idle, Walk };

class CAnimation : public Component {
 public:
  CAnimation(Object* owner);
  void Awake() override;
  void Update(float deltaTime) override;
  void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);
  void SetAnimationState(AnimationState state);
  const AnimationState& GetAnimationState() const;

 private:
  std::shared_ptr<CSprite> sprite;
  std::map<AnimationState, std::shared_ptr<Animation>> animations;
  std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};

#endif
