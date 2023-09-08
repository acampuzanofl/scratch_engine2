#include "SceneGame.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <string>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "CBoxCollider.hpp"
#include "CCamera.hpp"
#include "CCollider.hpp"
#include "CDrawable.hpp"
#include "CKeyboardAttack.hpp"
#include "CKeyboardMovement.hpp"
#include "CSprite.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"
#include "Debug.hpp"
#include "Input.hpp"
#include "ResourceAllocator.hpp"
#include "SpriteMap.hpp"
#include "Window.hpp"
#include "WorkingDirectory.hpp"

SceneGame::SceneGame(WorkingDirectory &workingDir,
                     ResourceAllocator<sf::Texture> &textureAllocator,
                     ResourceAllocator<SpriteMap> &spriteMapAllocator,
                     Window &window)
    : textureAllocator(textureAllocator),
      spriteMapAllocator(spriteMapAllocator),
      assetsDir(workingDir),
      window(window) {}

void SceneGame::OnCreate() {
  // create a temporary player object
  std::shared_ptr<Object> player = std::make_shared<Object>();
  player->transform->SetPosition(630.f, 380.f);  // set a starting position

  // player2
  std::shared_ptr<Object> player2 = std::make_shared<Object>();
  player2->transform->SetPosition(230.f, 300.f);  // set a starting position

  // Add a sprite component to the player
  auto sprite = player->AddComponent<CSprite>();

  // Add a sprite component to the player
  auto sprite2 = player2->AddComponent<CSprite>();

  // set texture and spritemap allocator for csprite component
  sprite->SetAllocator(&textureAllocator);
  sprite->SetAllocator(&spriteMapAllocator);
  sprite->SetDrawLayer(DrawLayer::Entities);

  // set texture and spritemap allocator for csprite component
  sprite2->SetAllocator(&textureAllocator);
  sprite2->SetAllocator(&spriteMapAllocator);
  sprite2->SetDrawLayer(DrawLayer::Entities);

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

  // add keyboard component for player
  auto movement = player->AddComponent<CKeyboardMovement>();
  auto attack = player->AddComponent<CKeyboardAttack>();

  // add keyboard component for player
  auto movement2 = player2->AddComponent<CKeyboardMovement>();

  // setting defualt keymap for player1
  Input::KeyMap player1map;
  player1map[Input::Key::Left] = sf::Keyboard::A;
  player1map[Input::Key::Right] = sf::Keyboard::D;
  player1map[Input::Key::Up] = sf::Keyboard::W;
  player1map[Input::Key::Down] = sf::Keyboard::S;
  player1map[Input::Key::B] = sf::Keyboard::J;

  // debugging events
  player1map[Input::Key::Zoomin] = sf::Keyboard::Q;
  player1map[Input::Key::Zoomout] = sf::Keyboard::E;
  input.SubscribeToKeys(player1map);

  // setting defualt keymap for player2
  Input::KeyMap player2map;
  player2map[Input::Key::Left] = sf::Keyboard::Left;
  player2map[Input::Key::Right] = sf::Keyboard::Right;
  player2map[Input::Key::Up] = sf::Keyboard::Up;
  player2map[Input::Key::Down] = sf::Keyboard::Down;
  input2.SubscribeToKeys(player2map);

  // setting input object for movement component
  movement->SetInput(&input);
  // setting input object for attack component
  attack->SetInput(&input);

  // setting input object for movement component
  movement2->SetInput(&input2);

  // add animation component
  auto animation = player->AddComponent<CAnimation>();

  // add animation component
  auto animation2 = player2->AddComponent<CAnimation>();

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> idleAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerIdle", .1f);
  std::shared_ptr<Animation> walkAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerWalk", .1f);
  std::shared_ptr<Animation> BAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerB", .05f);

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> mashidleAnimation =
      sprite2->CreateAnimationFromSpriteMap("MashIdle", .1f);

  // add the created animation to the animation component
  animation->AddAnimation(AnimationState::Idle, idleAnimation);
  animation->AddAnimation(AnimationState::Walk, walkAnimation);
  animation->AddAnimation(AnimationState::B, BAnimation);

  // add the created animation to the animation component
  animation2->AddAnimation(AnimationState::Idle, mashidleAnimation);

  // add collider component
  auto collider = player->AddComponent<CBoxCollider>();
  collider->SetSize(100, 200);
  collider->SetLayer(CollisionLayer::Player);

  // add collider component
  auto collider2 = player2->AddComponent<CBoxCollider>();
  collider2->SetSize(100, 200);
  collider2->SetOffset(0.f, 80.f);
  collider2->SetLayer(CollisionLayer::Player);

  /**
   * create a camera component and add it to player1
   * TODO camera is a component of the player but maybe
   * it makes more sense for the camera to be a component of the scene
   * have to check implementatinos for fighting games to learn
   * what makes the most sense
   */

  auto camera = player->AddComponent<CCamera>();
  camera->SetWindow(&window);
  camera->SetInput(&input);

  // add velocity component to player
  auto velocity = player->AddComponent<CVelocity>();

  // add player object to the ObjectCollector
  objects.Add(player);

  // add player object to the ObjectCollector
  objects.Add(player2);
}

void SceneGame::OnActivate() {}
void SceneGame::OnDestroy() {}
void SceneGame::ProcessInput() {
  /**
   *  TODO make an object collector for things with inputs and keyboard
   *  components. So that we only need to call objects.PollKey and process the
   *  inputs only if theres objects that are looking for inputs
   */

  input.PollKey();
  input2.PollKey();
}
void SceneGame::LateUpdate(float deltaTime) { objects.LateUpdate(deltaTime); }
void SceneGame::Update(float deltaTime) {
  objects.ProcessRemovals();
  objects.ProcessNewObjects();
  objects.Update(deltaTime);
}
void SceneGame::Draw(Window &window) {
  objects.Draw(window);
  Debug::Draw(window);
}