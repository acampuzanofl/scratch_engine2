#include "FrameLoader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "Animation.hpp"

FrameLoader::FrameLoader() {}

void FrameLoader::LoadJson(const std::string& fileName) {
  std::fstream f(fileName);
  jsonData = json::parse(f);
}

std::map<std::string, json> FrameLoader::GetFrames(
    const std::string& animationName) {
  std::shared_ptr<Animation> animation = std::make_shared<Animation>();

  //   std::vector<std::string> sorted;
  std::map<std::string, json> sorted;
  for (const auto& it : jsonData["frames"]) {
    auto filename = it["filename"].dump();
    if (filename.compare(1, animationName.size(), animationName, 0,
                         animationName.size()) == 0) {
      sorted[filename] = it["frame"];
    }
  }

  return sorted;
}

std::shared_ptr<Animation> FrameLoader::CreateAnimation(
    int textureId, const std::string& animationName) {
  auto frames = GetFrames(animationName);
  std::shared_ptr<Animation> animation = std::make_shared<Animation>();
  for (auto& it : frames) {
    animation->AddFrame(textureId, std::stoi(it.second["x"].dump()),
                        std::stoi(it.second["y"].dump()),
                        std::stoi(it.second["w"].dump()),
                        std::stoi(it.second["h"].dump()), 1);
  }
  return animation;
}