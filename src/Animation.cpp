#include "Animation.hpp"

#include <cassert>
#include <iostream>
#include <memory>

Animation::Animation(FacingDirection direction)
    : currentFrame(0), currentFrameTime(0.f), currentDirection(direction) {}

void Animation::SetDirection(FacingDirection dir) {
  if (currentDirection != dir) {
    currentDirection = dir;
    for (auto& f : *frames) {
      f.framex += f.framewidth;
      f.framewidth *= -1;
    }
  }
}

FacingDirection Animation::GetCurrentDirection() const {
  return currentDirection;
}

void Animation::AddFrame(int textureID, int x, int y, int width, int height,
                         float frameTIme) {
  SpriteMapData data = {0};
  data.id = textureID;
  data.framex = x;
  data.framey = y;
  data.framewidth = width;
  data.frameheight = height;
  data.displayTimeSeconds = frameTIme;
  frames->push_back(data);
}

void Animation::AddFrameList(
    std::shared_ptr<std::vector<SpriteMapData>> frameData) {
  frames = frameData;
}

const SpriteMapData* Animation::GetCurrentFrame() const {
  assert(frames != nullptr);
  assert(frames->size() > 0);

  return &(*frames)[currentFrame];
}

bool Animation::Update(float deltaTime) {
  assert(frames != nullptr);
  assert(frames->size() > 0);

  currentFrameTime += deltaTime;
  if (currentFrameTime >= (*frames)[currentFrame].displayTimeSeconds) {
    currentFrameTime = 0.f;
    IncrementFrame();
    return true;
  }
  return false;
}

void Animation::IncrementFrame() {
  currentFrame = (currentFrame + 1) % frames->size();
}

void Animation::Reset() {
  currentFrame = 0;
  currentFrameTime = 0.f;
}

// debugging functions
const int Animation::GetCurrentFrameIndex() const { return currentFrame; }
const int Animation::GetAnimationSize() const { return frames->size(); }