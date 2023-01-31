#include "SceneSplashScreen.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDirectory,
                                     SceneStateMachine& sceneStateMachine,
                                     Window& window,
                                     ResourceAllocator<sf::Texture>& allocator)
    : workingDirectory(workingDirectory),
      sceneStateMachine(sceneStateMachine),
      window(window),
      showForSeconds(0.f),
      currentSeconds(0.f),
      switchToState(0),
      allocator(allocator){};

void SceneSplashScreen::OnCreate() {
  // add the texture to the allocator
  int id = allocator.Add(workingDirectory.Get() + "splash/splash.png");

  // check if texture was succesfully added
  // if it was, load the texture and set the sprite
  if (id >= 0) {
    std::shared_ptr<sf::Texture> texture = allocator.Get(id);
    splashSprite.setTexture(*texture);
  }

  // grab the local coordinates of the sprite
  sf::FloatRect spriteSize = splashSprite.getLocalBounds();

  // set origin of sprite to center of image
  splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
  splashSprite.setScale(0.8f, 0.8f);

  // position sprite to center of screen
  sf::Vector2u windowCenter = window.GetCenter();
  splashSprite.setPosition(windowCenter.x, windowCenter.y);
}

void SceneSplashScreen::OnActivate() { currentSeconds = 0.f; }
void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::SetSwitchToScene(unsigned int id) {
  switchToState = id;
}

void SceneSplashScreen::Update(float deltaTime) {
  currentSeconds += deltaTime;
  if (currentSeconds >= showForSeconds) {
    sceneStateMachine.SwitchTo(switchToState);
  }
}

void SceneSplashScreen::Draw(Window& window) { window.Draw(splashSprite); }
