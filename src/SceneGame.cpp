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
#include "CMovementAnimation.hpp"
#include "CSprite.hpp"
#include "CVelocity.hpp"
#include "Component.hpp"
#include "Debug.hpp"
#include "Input.hpp"
#include "ResourceAllocator.hpp"
#include "SpriteMap.hpp"
#include "Window.hpp"
#include "WorkingDirectory.hpp"
#include "CDirection.hpp"
#include "CProjectileAttack.hpp"

SceneGame::SceneGame(WorkingDirectory &workingDir,
                     ResourceAllocator<sf::Texture> &textureAllocator,
                     ResourceAllocator<SpriteMap> &spriteMapAllocator,
                     Window &window)
    : textureAllocator(textureAllocator),
      spriteMapAllocator(spriteMapAllocator),
      assetsDir(workingDir),
      window(window) {}

void SceneGame::OnCreate() {

backgroundContext.input = nullptr;
backgroundContext.objects = &objects;
backgroundContext.spriteMapAllocator = nullptr;
backgroundContext.textureAllocator = &textureAllocator;
backgroundContext.window = &window;
backgroundContext.workingDir = &assetsDir;

auto background = std::make_shared<Object>(&backgroundContext);

// position sprite to center of screen
sf::Vector2f windowCenter = window.GetCenter();

// add the texture to the allocator
auto backgroundCSprite = background->AddComponent<CSprite>();
backgroundCSprite->Load(assetsDir.Get() + "backgrounds/grid.jpg");
backgroundCSprite->SetDrawLayer(DrawLayer::Background);

objects.Add(background);

  // Zoom out at start to help see both characters, should be handled by automatically, this is a hot fix.
  sf::View view = window.GetView();
  view.zoom(1.5);
  window.SetView(view);

  /**
   * TODO
   * make an allocator for the input so that the scene
   * can container knowledge of different inputs?
   * idk if thats the best way to do it, we can make 2 different contexts, 1 per
   * player
   */
  context.input = &input;
  context.objects = &objects;
  context.workingDir = &assetsDir;
  context.textureAllocator = &textureAllocator;
  context.spriteMapAllocator = &spriteMapAllocator;
  context.window = &window;

  /**
  * TODO
  * instead of building player 1 and 2 seperatly
  * make a function that can build a player and return
  * it so i only need to modifiy one function to prevent
  * missing initializers
  */

 /**
  * TODO:
  * having 2 different contexts seems like a bad way of doing this
  * should find and alternative that allows me to use context
  */

  context2.input = &input2;
  context2.objects = &objects;
  context2.workingDir = &assetsDir;
  context2.textureAllocator = &textureAllocator;
  context2.spriteMapAllocator = &spriteMapAllocator;
  context2.window = &window;

  // create a temporary player object
  std::shared_ptr<Object> player = std::make_shared<Object>(&context);
  player->transform->SetPosition(630.f, 380.f);  // set a starting position

  // player2
  std::shared_ptr<Object> player2 = std::make_shared<Object>(&context2);
  player2->transform->SetPosition(230.f, 300.f);  // set a starting position

  // Add a sprite component to the player
  auto sprite = player->AddComponent<CSprite>();

  // Add a sprite component to the player
  auto sprite2 = player2->AddComponent<CSprite>();

  // set texture and spritemap allocator for csprite component
  sprite->SetDrawLayer(DrawLayer::Entities);

  // set texture and spritemap allocator for csprite component
  sprite2->SetDrawLayer(DrawLayer::Entities);

  // add texture and sprite map using load
  sprite->Load(
      assetsDir.Get() +
          "characters/Wagner/WagnerSpriteSheet/WagnerSpriteSheet.png",
      assetsDir.Get() +
          "characters/Wagner/WagnerSpritesheet/WagnerSpriteSheet.json");

  // add texture and sprite map using Load
  sprite2->Load(
      assetsDir.Get() + "characters/Hyde/HydeSpriteSheet/HydeSpriteSheet.png",
      assetsDir.Get() + "characters/Hyde/HydeSpritesheet/HydeSpriteSheet.json");

  // add keyboard component for player
  auto movement = player->AddComponent<CKeyboardMovement>();
  auto attack = player->AddComponent<CKeyboardAttack>();

  // add keyboard component for player
  auto movement2 = player2->AddComponent<CKeyboardMovement>();
  auto attack2 = player2->AddComponent<CKeyboardAttack>();


  // setting defualt keymap for player1
  Input::KeyMap player1map;
  player1map[Input::Key::Left] = sf::Keyboard::Key::A;
  player1map[Input::Key::Right] = sf::Keyboard::Key::D;
  player1map[Input::Key::Up] = sf::Keyboard::Key::W;
  player1map[Input::Key::Down] = sf::Keyboard::Key::S;
  player1map[Input::Key::B] = sf::Keyboard::Key::J;

  // debugging events
  player1map[Input::Key::Zoomin] = sf::Keyboard::Key::Q;
  player1map[Input::Key::Zoomout] = sf::Keyboard::Key::E;
  input.SubscribeToKeys(player1map);

  // setting default keymap for player2
  Input::KeyMap player2map;
  player2map[Input::Key::Left] = sf::Keyboard::Key::Left;
  player2map[Input::Key::Right] = sf::Keyboard::Key::Right;
  player2map[Input::Key::Up] = sf::Keyboard::Key::Up;
  player2map[Input::Key::Down] = sf::Keyboard::Key::Down;
  player2map[Input::Key::B] = sf::Keyboard::Key::RShift;
  input2.SubscribeToKeys(player2map);

  // add animation component
  auto animation = player->AddComponent<CAnimation>();

  // add animation component
  auto animation2 = player2->AddComponent<CAnimation>();

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> idleAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerIdle", .1f, true);
  std::shared_ptr<Animation> walkAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerWalk", .1f, true);
  std::shared_ptr<Animation> BAnimation =
      sprite->CreateAnimationFromSpriteMap("WagnerB", .05f);

  // create an animation using the sprite map and sprite sheet
  std::shared_ptr<Animation> hydeidleAnimation =
      sprite2->CreateAnimationFromSpriteMap("HydeIdle", .1f, true);
  std::shared_ptr<Animation> hydefireballAnimation =
      sprite2->CreateAnimationFromSpriteMap("HydeFireball", .05f);

  // add the created animation to the animation component
  animation->AddAnimation(AnimationState::Idle, idleAnimation);
  animation->AddAnimation(AnimationState::Walk, walkAnimation);
  animation->AddAnimation(AnimationState::B, BAnimation);

  // add the created animation to the animation component
  /**
   * TODO:
   * Adding animation state D causes a bus error
   */
  animation2->AddAnimation(AnimationState::Idle, hydeidleAnimation);
  animation2->AddAnimation(AnimationState::B, hydefireballAnimation);


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

  // add velocity component to player
  auto velocity = player->AddComponent<CVelocity>();
  auto velocity2 = player2->AddComponent<CVelocity>();


  // add direction componennt
  auto direction = player->AddComponent<CDirection>();
  auto direction2 = player2->AddComponent<CDirection>();


  // add movement animation to player
  auto movementanim = player->AddComponent<CMovementAnimation>();
  auto movementanim2 = player2->AddComponent<CMovementAnimation>();

  // give player2 a projectile
  auto hydefireball = player2->AddComponent<CProjectileAttack>();

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