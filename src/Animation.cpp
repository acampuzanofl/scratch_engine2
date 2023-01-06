#include "Animation.hpp"

Animation::Animation() : frames(0), currentFrame(0), currentFrameTime(0) {}

void Animation::AddFrame(int textureID, int x, int y, int width, int height,
                         float frameTIme) {
  FrameData data;
  data.id = textureID;
  data.x = x;
  data.y = y;
  data.width = width;
  data.height = height;
  data.displayTimeSeconds = frameTIme;
  frames.push_back(data);
}

void Animation::AddFrame(FrameData frameData) { frames.push_back(frameData); }

const FrameData* Animation::GetCurrentFrame() const {
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