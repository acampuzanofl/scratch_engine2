#ifndef spritemap_hpp
#define spritemap_hpp
#include <memory>
#include <string>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

struct SpriteMapData {
  int id = 0;           // id supplied from allocator
  int framex = 0;       // x position in sprite sheet
  int framey = 0;       // y position in sprite sheet
  int framewidth = 0;   // width position in sprite sheet
  int frameheight = 0;  // height position in sprite sheet
  int sourceSizex = 0;
  int sourceSizey = 0;
  int sourceSizewidth = 0;
  int sourceSizeheight = 0;
  int sourceheight = 0;
  int sourcewidth = 0;
  bool isRotated = 0;
  float displayTimeSeconds = 0;  // time from is displayed for
};

class SpriteMap {
 public:
  SpriteMap();
  // json file generated using free texture packer
  // https://github.com/odrick/free-tex-packer
  bool loadFromFile(const std::string &fileName);
  std::shared_ptr<std::vector<SpriteMapData>> CreateSpriteMapData(
      int textureId, const std::string &animationName, float animationSpeed);
  std::map<std::string, json> GetFrames(const std::string &animationName);

 private:
  json jsonData;
};

#endif