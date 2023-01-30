#ifndef spritemap_hpp
#define spritemap_hpp
#include <memory>
#include <string>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

struct SpriteMapData {
  int id;           // id supplied from allocator
  int framex;       // x position in sprite sheet
  int framey;       // y position in sprite sheet
  int framewidth;   // width position in sprite sheet
  int frameheight;  // height position in sprite sheet
  int sourceSizex;
  int sourceSizey;
  int sourceSizewidth;
  int sourceSizeheight;
  int sourceheight;
  int sourcewidth;
  bool isRotated;
  float displayTimeSeconds;  // time from is displayed for
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