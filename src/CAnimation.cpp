#include "CAnimation.hpp"

#include <iostream>
#include <utility>

#include "Animation.hpp"
#include "Component.hpp"
#include "Object.hpp"

CAnimation::CAnimation(Object* owner)
    : Component(owner), currentAnimation(AnimationState::None, nullptr) {}

void CAnimation::Awake() { sprite = owner->GetComponent<CSprite>(); }

void CAnimation::Update(float deltaTime) {
  if (currentAnimation.first != AnimationState::None) {
    bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);
    if (newFrame) {
      const FrameData* data = currentAnimation.second->GetCurrentFrame();
      sprite->Load(data->id);
      sprite->SetTextureRect(data->x, data->y, data->width, data->height);
      // debug
      // sprite->SetPivot(data->pivotx, date->pivoty);
    }
  }
}

void CAnimation::AddAnimation(AnimationState state,
                              std::shared_ptr<Animation> animation) {
  auto inserted = animations.insert(std::make_pair(state, animation));
  if (currentAnimation.first == AnimationState::None) {
    SetAnimationState(state);
  }
}

void CAnimation::SetAnimationState(AnimationState state) {
  if (currentAnimation.first == state) {
    return;
  }
  auto animation = animations.find(state);
  if (animation != animations.end()) {
    currentAnimation.first = animation->first;
    currentAnimation.second = animation->second;
    currentAnimation.second->Reset();
  }
}

const AnimationState& CAnimation::GetAnimationState() const {
  return currentAnimation.first;
}