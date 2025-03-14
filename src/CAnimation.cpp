#include "CAnimation.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <utility>

#include "Animation.hpp"
#include "Component.hpp"
#include "Debug.hpp"
#include "Object.hpp"
#include "SpriteMap.hpp"

CAnimation::CAnimation(Object *owner)
    : Component(owner), currentAnimation(AnimationState::None, nullptr) {}

void CAnimation::Awake() {
  sprite = owner->GetComponent<CSprite>();
  direction = owner->GetComponent<CDirection>();

  // TODO: CAnimation being dependent on owner having a CDirection doesnt make sense to me? I'm not sure, will have to think about it. Also need to assert all componenent dependencies 
  assert(direction != nullptr);
  assert(sprite != nullptr);
  
  // make sure theres an animation
  // if there is an animation, initialize the first frame of animation on awake
  if (currentAnimation.first != AnimationState::None) {
    SetCurrentFrame();
  }
}

void CAnimation::Update(float deltaTime) {
  SetAnimationDirection(direction->Get());
  if (currentAnimation.first != AnimationState::None) {
    bool newFrame = currentAnimation.second->Update(deltaTime);
    if (newFrame) {
      SetCurrentFrame();
    }
  }
}

void CAnimation::AddAnimation(AnimationState state,
                              std::shared_ptr<Animation> animation) {
  animations.insert(std::make_pair(state, animation));
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

void CAnimation::SetAnimationDirection(FacingDirection facing){
    direction->Set(facing);
}


const AnimationState &CAnimation::GetCurrentAnimationState() const {
  return currentAnimation.first;
}

const std::shared_ptr<Animation> &CAnimation::GetCurrentAnimation() const {
  return currentAnimation.second;
}

void CAnimation::SetCurrentFrame() {
  const SpriteMapData *currentFrame =
      currentAnimation.second->GetCurrentFrame();
  sprite->Load(currentFrame->id);
  sprite->SetTextureRect(currentFrame->framex, currentFrame->framey,
                         currentFrame->framewidth, currentFrame->frameheight);
}

const std::shared_ptr<Animation> &CAnimation::GetAnimationByState(
    AnimationState state) const {
  return animations.find(state)->second;
}