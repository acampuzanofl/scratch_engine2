#include "SpriteMap.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

#include "Animation.hpp"

SpriteMap::SpriteMap() {}

/**
 * json file generated using free texture packer
 * https://github.com/odrick/free-tex-packer
 */
bool SpriteMap::loadFromFile(const std::string &fileName) {
  std::fstream f(fileName);
  jsonData = json::parse(f);

  if (jsonData == nullptr) {
    return false;
  }
  return true;
}

std::map<std::string, json> SpriteMap::GetFrames(
    const std::string &animationName) {
  std::map<std::string, json> sorted;
  for (const auto &it : jsonData["frames"]) {
    auto filename = it["filename"].dump();
    if (filename.compare(1, animationName.size(), animationName, 0,
                         animationName.size()) == 0) {
      sorted[filename] = it;
    }
  }
  if (sorted.empty()) {
    std::cout << "\033[91merror: \033[0m"
              << "\"" << animationName << "\""
              << " was not found in this SpriteMap. And i don't know how to "
                 "handle errors so i'm just gana close the game :(\n";
    exit(EXIT_FAILURE);
  }
  return sorted;
}
/**
 * json file generated using free texture packer
 * https://github.com/odrick/free-tex-packer
 */
std::shared_ptr<std::vector<SpriteMapData>> SpriteMap::CreateSpriteMapData(
    int textureId, const std::string &animationName, float animationSpeed) {
  auto frames = GetFrames(animationName);

  std::vector<SpriteMapData> frameDataList;
  SpriteMapData frameData;
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
    frameData.sourcewidth = std::stoi(it.second["sourceSize"]["w"].dump());
    frameData.sourceheight = std::stoi(it.second["sourceSize"]["h"].dump());
    frameData.isRotated = (it.second["rotated"].dump().compare("true") == 0);
    frameData.displayTimeSeconds = animationSpeed;
    frameDataList.push_back(frameData);
  }

  return std::make_shared<std::vector<SpriteMapData>>(frameDataList);
}