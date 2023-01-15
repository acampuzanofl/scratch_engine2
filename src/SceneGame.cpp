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
  player->transform->SetPosition(200.f, 0.f);  // set a starting position

  // player2
  std::shared_ptr<Object> player2 = std::make_shared<Object>();
  player2->transform->SetPosition(-200.f, -150.f);  // set a starting position

  // Add a sprite component to the player
  auto sprite = player->AddComponent<CSprite>();

  // Add a sprite component to the player
  auto sprite2 = player2->AddComponent<CSprite>();

  // set texture and spritemap allocator for csprite component
  sprite->SetAllocator(&textureAllocator);
  sprite->SetAllocator(&spriteMapAllocator);

  // set texture and spritemap allocator for csprite component
  sprite2->SetAllocator(&textureAllocator);
  sprite2->SetAllocator(&spriteMapAllocator);

  // add texture and sprite map using load
  sprite->Load(
      assetsDir.Get() +
          "characters/Wagner/WagnerSpriteSheet/WagnerSpriteSheet.png",
      assetsDir.Get() +
          "characters/Wagner/WagnerSpritesheet/WagnerSpriteSheet.json");

  // add texture and sprite map using Load
  sprite2->Load(
      assetsDir.Get() + "characters/Mash/MashSpriteSheet/MashSpriteSheet.png",
      assetsDir.Get() + "characters/Mash/MashSpritesheet/MashSpriteSheet.json");

  // add keyboard input component for player
  auto movement = player->AddComponent<CKeyboardMovement>();

  // add keyboard input component for player
  auto movement2 = player2->AddComponent<CKeyboardMovement>();

  // setting input object for movement component
  movement->SetInput(&input);

  // setting input object for movement component
  movement2->SetInput(&input);

  // add animation component
  auto animation = player->AddComponent<CAnimation>();

  // add animation component
  auto animation2 = player2->AddComponent<CAnimation>();

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> idleAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerIdle", .1f);
  std::shared_ptr<Animation> walkAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerWalk", .1f);

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> mashidleAnimation =
      sprite2->CreateAnimationFromSpriteMap("MashIdle", .1f);

  // add the created animation to the animation component
  animation->AddAnimation(AnimationState::Idle, idleAnimation);
  animation->AddAnimation(AnimationState::Walk, walkAnimation);

  // add the created animation to the animation component
  animation2->AddAnimation(AnimationState::Idle, mashidleAnimation);

  // add player object to the ObjectCollector
  objects.Add(player);

  // add player object to the ObjectCollector
  objects.Add(player2);
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