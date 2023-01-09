#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
struct SpriteFrameData {
  int id;                         // id supplied from allocator
  int framex;                     // x position in sprite sheet
  int framey;                     // y position in sprite sheet
  int framewidth;                 // width position in sprite sheet
  int frameheight;                // height position in sprite sheet
  int sourceSizex;
  int sourceSizey;
  int sourceSizewidth;
  int sourceSizeheight;
  bool isRotated;
  float displayTimeSeconds;  // time from is displayed for
};


// Animation class defines and creates animations
// an animation is a collection of "Frames"
// a Frame is position information witin an atlas
class Animation {
 public:
  Animation();
  void AddFrame(int textureID, int x, int y, int width, int height,
                float frameTime);
  void AddFrameList(std::vector<SpriteFrameData> frameList);
  const SpriteFrameData* GetCurrentFrame() const;
  bool UpdateFrame(float deltaTime);
  void Reset();

 private:
  void IncrementFrame();
  std::vector<SpriteFrameData> frames;
  int currentFrame;
  float currentFrameTime;
};

#endif
