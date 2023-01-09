#include "CAnimation.hpp"

#include <iostream>
#include <memory>
#include <utility>

#include "Animation.hpp"
#include "Component.hpp"
#include "Object.hpp"
#include "SpriteMap.hpp"

CAnimation::CAnimation(Object *owner)
    : Component(owner), currentAnimation(AnimationState::None, nullptr) {}

void CAnimation::Awake() { sprite = owner->GetComponent<CSprite>(); }

void CAnimation::Update(float deltaTime) {
  if (currentAnimation.first != AnimationState::None) {
    bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);
    if (newFrame) {
      const SpriteMapData *currentFrame =
          currentAnimation.second->GetCurrentFrame();
      sprite->Load(currentFrame->id);
      sprite->SetTextureRect(currentFrame->framex, currentFrame->framey,
                             currentFrame->framewidth,
                             currentFrame->frameheight);
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

const AnimationState &CAnimation::GetCurrentAnimationState() const {
  return currentAnimation.first;
}

const std::shared_ptr<Animation> &CAnimation::GetCurrentAnimation() const {
  return currentAnimation.second;
}