#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>

#include "SpriteMap.hpp"

// Animation class defines and creates animations
// an animation is a collection of "Frames"
// a Frame is position information witin an atlas
class Animation {
 public:
  Animation();
  void AddFrame(int textureID, int x, int y, int width, int height,
                float frameTime);
  void AddFrameList(std::vector<SpriteMapData> frameList);
  const SpriteMapData* GetCurrentFrame() const;
  bool UpdateFrame(float deltaTime);
  void Reset();

 private:
  void IncrementFrame();
  std::vector<SpriteMapData> frames;
  int currentFrame;
  float currentFrameTime;
};

#endif
