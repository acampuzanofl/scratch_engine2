#ifndef frameloader_hpp
#define frameloader_hpp
#include <memory>
#include <string>

#include "Animation.hpp"
#include "json.hpp"
using json = nlohmann::json;

class FrameLoader {
 public:
  FrameLoader();
  void LoadJson(const std::string& fileName);
  std::shared_ptr<Animation> CreateAnimation(int textureId,
                                             const std::string& animationName);
  std::map<std::string, json> GetFrames(const std::string& animationName);

 private:
  json jsonData;
};

#endif