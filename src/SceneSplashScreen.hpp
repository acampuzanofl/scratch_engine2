#ifndef SCENESPLASHSCREEN_hpp
#define SCENESPLASHSCREEN_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceAllocator.hpp"
#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"

class SceneSplashScreen : public Scene {
 public:
  SceneSplashScreen(WorkingDirectory& workingDirectory,
                    SceneStateMachine& sceneStateMachine, Window& window,
                    ResourceAllocator<sf::Texture>& allocator);
  void OnCreate() override;
  void OnDestroy() override;
  void OnActivate() override;
  void Update(float deltaTime) override;
  void Draw(Window& window) override;
  void SetSwitchToScene(unsigned int id);

 private:
  std::optional<sf::Sprite> splashSprite;
  WorkingDirectory& workingDirectory;
  SceneStateMachine& sceneStateMachine;
  Window& window;
  float showForSeconds;
  float currentSeconds;
  unsigned int switchToState;
  ResourceAllocator<sf::Texture>& allocator;
};

#endif