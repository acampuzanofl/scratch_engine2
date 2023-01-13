#include "Animation.hpp"

Animation::Animation(FacingDirection direction)
    : frames(0),
      currentFrame(0),
      currentFrameTime(0.f),
      currentDirection(direction) {}

void Animation::SetDirection(FacingDirection dir) {
  if (currentDirection != dir) {
    currentDirection = dir;
    for (auto& f : frames) {
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
  frames.push_back(data);
}

void Animation::AddFrameList(std::vector<SpriteMapData> frameData) {
  frames = frameData;
}

const SpriteMapData* Animation::GetCurrentFrame() const {
  if (frames.size() > 0) {
    return &frames[currentFrame];
  }
  return nullptr;
}

bool Animation::UpdateFrame(float deltaTime) {
  if (frames.size() > 0) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frames[currentFrame].displayTimeSeconds) {
      currentFrameTime = 0.f;
      IncrementFrame();
      return true;
    }
  }
  return false;
}

void Animation::IncrementFrame() {
  currentFrame = (currentFrame + 1) % frames.size();
}

void Animation::Reset() {
  currentFrame = 0;
  currentFrameTime = 0.f;
}

// debugging functions
const int Animation::GetCurrentFrameIndex() const { return currentFrame; }
const int Animation::GetAnimationSize() const { return frames.size(); }