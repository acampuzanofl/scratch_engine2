#include "SceneSplashScreen.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"
#include "CSprite.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDirectory,
                                     SceneStateMachine& sceneStateMachine,
                                     Window& window,
                                     ResourceAllocator<sf::Texture>& allocator)
    : assetsDir(workingDirectory),
      sceneStateMachine(sceneStateMachine),
      window(window),
      showForSeconds(0.f),
      currentSeconds(0.f),
      switchToState(0),
      textureAllocator(allocator){};

void SceneSplashScreen::OnCreate() {

  context.input = nullptr;
  context.objects = &objects;
  context.workingDir = &assetsDir;
  context.textureAllocator = &textureAllocator;
  context.spriteMapAllocator = nullptr;
  context.window = &window;

  auto background = std::make_shared<Object>(&context);

  // add the texture to the allocator
  auto backgroundCSprite = background->AddComponent<CSprite>();
  backgroundCSprite->Load(assetsDir.Get() + "splash/splash.png");
  backgroundCSprite->SetDrawLayer(DrawLayer::Background);

  // position sprite to center of screen
  sf::Vector2f windowCenter = window.GetCenter();
  background->transform->SetPosition({windowCenter.x, windowCenter.y});

  objects.Add(background);
}

void SceneSplashScreen::OnActivate() { currentSeconds = 0.f; }
void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::SetSwitchToScene(unsigned int id) {
  switchToState = id;
}

void SceneSplashScreen::Update(float deltaTime) {

  objects.ProcessRemovals();
  objects.ProcessNewObjects();
  objects.Update(deltaTime);
  
  currentSeconds += deltaTime;
  if (currentSeconds >= showForSeconds) {
    sceneStateMachine.SwitchTo(switchToState);
  }
}

void SceneSplashScreen::Draw(Window& window) { 
  objects.Draw(window); 
  }
