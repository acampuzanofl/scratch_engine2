#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>
#include <vector>

#include "SpriteMap.hpp"

enum class FacingDirection { None, Left, Right };

// Animation class defines and creates animations
// an animation is a collection of "Frames"
// a Frame is position information witin an atlas
class Animation {
 public:
  Animation(FacingDirection direction);
  void AddFrame(int textureID, int x, int y, int width, int height,
                float frameTime);
  void AddFrameList(std::shared_ptr<std::vector<SpriteMapData>> frameList);
  const SpriteMapData* GetCurrentFrame() const;
  bool Update(float deltaTime);
  void Reset();
  void SetDirection(FacingDirection dir);
  FacingDirection GetCurrentDirection() const;

  // Debugging functions
  const int GetCurrentFrameIndex() const;
  const int GetAnimationSize() const;

 private:
  void IncrementFrame();
  std::shared_ptr<std::vector<SpriteMapData>> frames;
  int currentFrame;
  float currentFrameTime;
  FacingDirection currentDirection;
};

#endif
