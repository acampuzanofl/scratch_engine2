#ifndef frameloader_hpp
#define frameloader_hpp
#include <memory>
#include <string>
#include <vector>

#include "Animation.hpp"
#include "json.hpp"
using json = nlohmann::json;

class FrameLoader {
 public:
  FrameLoader();
  void LoadJson(const std::string& fileName);
  std::vector<SpriteFrameData> CreateSpriteFrameData(int textureId,
                                             const std::string& animationName, float animationSpeed);
  std::map<std::string, json> GetFrames(const std::string& animationName);

 private:
  json jsonData;
};

#endif