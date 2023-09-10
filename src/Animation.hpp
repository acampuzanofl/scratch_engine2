#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <functional>
#include <memory>
#include <vector>

#include "Bitmask.hpp"
#include "SpriteMap.hpp"

using FrameCallback = std::function<void(void)>;

// Animation class defines and creates animations
// an animation is a collection of "Frames"
// a Frame is position information witin an atlas
class Animation {
 public:
  Animation();
  void AddFrame(int textureID, int x, int y, int width, int height,
                float frameTime, bool looped);
  void AddFrameList(std::shared_ptr<std::vector<SpriteMapData>> frameList,
                    bool loop);
  const SpriteMapData* GetCurrentFrame() const;
  bool Update(float deltaTime);
  void Reset();
  void AddFrameCallback(unsigned int frame, FrameCallback callback);
  void SetLooped(bool looped);
  bool isLooped();

  // Debugging functions
  int GetCurrentFrameIndex() const;
  int GetAnimationSize() const;

 private:
  void IncrementFrame();
  void DoCallbacks();
  std::shared_ptr<std::vector<SpriteMapData>> frames;
  unsigned int currentFrame;
  float currentFrameTime;
  std::map<int, std::vector<FrameCallback>> callbacks;
  Bitmask callbackMask;
  bool isLoop;
};

#endif
