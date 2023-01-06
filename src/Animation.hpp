#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
struct FrameData {
  int id;                    // id supplied from allocator
  int x;                     // x position in sprite sheet
  int y;                     // y position in sprite sheet
  int width;                 // width position in sprite sheet
  int height;                // height position in sprite sheet
  float displayTimeSeconds;  // time from is displayed for
};

class Animation {
 public:
  Animation();
  void AddFrame(int textureID, int x, int y, int width, int height,
                float frameTime);
  void AddFrame(FrameData frameData);
  const FrameData* GetCurrentFrame() const;
  bool UpdateFrame(float deltaTime);
  void Reset();

 private:
  void IncrementFrame();
  std::vector<FrameData> frames;
  int currentFrame;
  float currentFrameTime;
};

#endif
