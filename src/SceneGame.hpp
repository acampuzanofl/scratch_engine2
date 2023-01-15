#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "CKeyboardMovement.hpp"
#include "CSprite.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "ObjectCollection.hpp"
#include "ResourceAllocator.hpp"
#include "Scene.hpp"
#include "SpriteMap.hpp"
#include "Window.hpp"
#include "WorkingDirectory.hpp"

class SceneGame : public Scene {
 public:
  SceneGame(WorkingDirectory &workingDir,
            ResourceAllocator<sf::Texture> &textureAllocator,
            ResourceAllocator<SpriteMap> &spriteMap);
  void OnCreate() override;
  void OnDestroy() override;
  void OnActivate() override;
  void ProcessInput() override;
  void LateUpdate(float deltaTime) override;
  void Update(float deltaTime) override;
  void Draw(Window &window) override;

 private:
  ResourceAllocator<sf::Texture> &textureAllocator;
  ResourceAllocator<SpriteMap> &spriteMapAllocator;
  WorkingDirectory &assetsDir;
  Input input;
  Input input2;
  ObjectCollection objects;
};

#endif