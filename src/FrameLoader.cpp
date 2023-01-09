#include "FrameLoader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#include "Animation.hpp"

FrameLoader::FrameLoader() {}

void FrameLoader::LoadJson(const std::string &fileName) {
  std::fstream f(fileName);
  jsonData = json::parse(f);
}

std::map<std::string, json>
FrameLoader::GetFrames(const std::string &animationName) {
  std::shared_ptr<Animation> animation = std::make_shared<Animation>();

  //   std::vector<std::string> sorted;
  std::map<std::string, json> sorted;
  for (const auto &it : jsonData["frames"]) {
    auto filename = it["filename"].dump();
    if (filename.compare(1, animationName.size(), animationName, 0,
                         animationName.size()) == 0) {
      sorted[filename] = it;
    }
  }

  return sorted;
}

std::vector<SpriteFrameData> FrameLoader::CreateSpriteFrameData(
    int textureId, const std::string &animationName, float animationSpeed) {
  auto frames = GetFrames(animationName);

  std::vector<SpriteFrameData> frameDataList;
  SpriteFrameData frameData;
  for (auto &it : frames) {
    frameData.id = textureId;
    frameData.framex = std::stoi(it.second["frame"]["x"].dump());
    frameData.framey = std::stoi(it.second["frame"]["y"].dump());
    frameData.framewidth = std::stoi(it.second["frame"]["w"].dump());
    frameData.frameheight = std::stoi(it.second["frame"]["h"].dump());
    frameData.sourceSizex =
        std::stoi(it.second["spriteSourceSize"]["x"].dump());
    frameData.sourceSizey =
        std::stoi(it.second["spriteSourceSize"]["y"].dump());
    frameData.sourceSizewidth =
        std::stoi(it.second["spriteSourceSize"]["w"].dump());
    frameData.sourceSizeheight =
        std::stoi(it.second["spriteSourceSize"]["h"].dump());
    frameData.isRotated = (it.second["rotated"].dump().compare("true") == 0);
    frameData.displayTimeSeconds = animationSpeed;
    frameDataList.push_back(frameData);
  }
  return frameDataList;
}