#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

#include "Input.hpp"
#include "ResourceAllocator.hpp"
#include "SceneGame.hpp"
#include "SceneSplashScreen.hpp"
#include "SceneStateMachine.hpp"
#include "Window.hpp"
#include "WorkingDirectory.hpp"

class Game {
 public:
  Game();

  void Update();
  void LateUpdate();
  void Draw();
  bool IsRunning() const;
  void CalculateDeltaTime();
  void ProcessInput();

 private:
  Window window;
  WorkingDirectory workingDir;
  sf::Clock clock;
  float deltaTime;
  SceneStateMachine sceneStateMachine;
  ResourceAllocator<sf::Texture> allocator;
};

#endif