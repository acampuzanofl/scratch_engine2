#include "SceneGame.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "CKeyboardMovement.hpp"
#include "CSprite.hpp"
#include "Component.hpp"
#include "ResourceAllocator.hpp"
#include "SpriteMap.hpp"
#include "WorkingDirectory.hpp"

SceneGame::SceneGame(WorkingDirectory &workingDir,
                     ResourceAllocator<sf::Texture> &textureAllocator,
                     ResourceAllocator<SpriteMap> &spriteMapAllocator)
    : assetsDir(workingDir),
      textureAllocator(textureAllocator),
      spriteMapAllocator(spriteMapAllocator) {}

void SceneGame::OnCreate() {
  // create a temporary player object
  std::shared_ptr<Object> player = std::make_shared<Object>();
  player->transform->SetPosition(0.f, 0.f);  // set a starting position

  // Add a sprite component to the player
  auto sprite = player->AddComponent<CSprite>();

  // set texture allocator for csprite component
  sprite->SetAllocator(&textureAllocator);

  // add movement component for player
  auto movement = player->AddComponent<CKeyboardMovement>();

  // setting input object for movement component
  movement->SetInput(&input);

  // add animation component
  auto animation = player->AddComponent<CAnimation>();

  // add texture using animation component
  int wagnerSpriteSheetId = textureAllocator.Add(
      assetsDir.Get() +
      "characters/Wagner/WagnerSpriteSheet/WagnerSpriteSheet.png");

  // add sprites to annimation
  std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

  // // testing frame loader
  SpriteMap frameLoader;
  frameLoader.loadFromFile(
      assetsDir.Get() +
      "characters/Wagner/WagnerSpritesheet/WagnerSpriteSheet.json");
  std::vector<SpriteMapData> wagnerIdleFrameList =
      frameLoader.CreateSpriteMapData(wagnerSpriteSheetId, "WagnerIdle", .1f);
  idleAnimation->AddFrameList(wagnerIdleFrameList);

  animation->AddAnimation(AnimationState::Idle, idleAnimation);

  // add player object to the ObjectCollector
  objects.Add(player);
}

void SceneGame::OnActivate() {}
void SceneGame::OnDestroy() {}
void SceneGame::ProcessInput() { input.PollKey(); }
void SceneGame::LateUpdate(float deltaTime) { objects.LateUpdate(deltaTime); }
void SceneGame::Update(float deltaTime) {
  objects.ProcessRemovals();
  objects.ProcessNewObjects();
  objects.Update(deltaTime);
}
void SceneGame::Draw(Window &window) { objects.Draw(window); }