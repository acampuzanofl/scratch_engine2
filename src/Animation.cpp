#include "Animation.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "SpriteMap.hpp"

Animation::Animation() : currentFrame(0), currentFrameTime(0.f), isLoop(true) {}

void Animation::AddFrame(int textureID, int x, int y, int width, int height,
                         float frameTIme, bool looped) {
  SpriteMapData data = {};
  data.id = textureID;
  data.framex = x;
  data.framey = y;
  data.framewidth = width;
  data.frameheight = height;
  data.displayTimeSeconds = frameTIme;
  frames->push_back(data);
  isLoop = looped;
}

void Animation::AddFrameList(
    std::shared_ptr<std::vector<SpriteMapData>> frameData, bool looped) {
  frames = frameData;
  isLoop = looped;
}

const SpriteMapData* Animation::GetCurrentFrame() const {
  assert(frames != nullptr);
  assert(frames->size() > 0);

  return &(*frames)[currentFrame];
}

bool Animation::Update(float deltaTime) {
  assert(frames != nullptr);
  assert(frames->size() > 0);

  // We now also check if animation is looped
  if (frames->size() > 1 && (isLoop || currentFrame < frames->size() - 1)) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= (*frames)[currentFrame].displayTimeSeconds) {
      currentFrameTime = 0.f;
      IncrementFrame();
      // TODO this will perform the action for the the frame is drawn?
      // test to see if this is janky and do we need to implement in another way
      DoCallbacks();
      return true;
    }
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
int Animation::GetCurrentFrameIndex() const { return currentFrame; }
int Animation::GetAnimationSize() const { return frames->size(); }

void Animation::AddFrameCallback(unsigned int frame, FrameCallback callback) {
  // if the requested frame is larger that the number of animation frames
  // then this request is ignored.
  if (frame < frames->size()) {
    auto framecallback = callbacks.find(frame);
    if (framecallback == callbacks.end()) {
      // if there is not an existing entry for this frame
      // we create one.
      // TODO this will only work for a maximum of 64 frames?
      // Thats probably not a problem but it could be
      callbackMask.SetBit(frame);
      callbacks.insert(
          std::make_pair(frame, std::vector<FrameCallback>{callback}));
    } else {
      // An existing entry was found so we
      // add the action to the vector
      framecallback->second.emplace_back(callback);
    }
  }
}

void Animation::DoCallbacks() {
  if (callbacks.size() > 0) {
    // TODO can use bitmask as quick way of checking if frame has an action
    if (callbackMask.GetBit(currentFrame)) {
      // iterate through the list of callbacks for the current frame and call
      // them
      auto framecallback = callbacks.at(currentFrame);
      for (auto f : framecallback) {
        f();
      }
    }
  }
}

bool Animation::isLooped() { return isLoop; }
void Animation::SetLooped(bool looped) { isLoop = looped; }