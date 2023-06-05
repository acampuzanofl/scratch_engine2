#include "Game.hpp"

#include <SFML/System/Vector2.hpp>
#include <memory>

#include "SceneGame.hpp"
#include "SceneSplashScreen.hpp"
#include "SpriteMap.hpp"

Game::Game() : window("scratch engine"), workingDir("assets") {
  // initialize scenes
  std::shared_ptr<SceneSplashScreen> splashScreen =
      std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window,
                                          textureAllocator);
  std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(
      workingDir, textureAllocator, spriteMapAllocator, window);

  // add scenes to map
  unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
  unsigned int gameSceneID = sceneStateMachine.Add(gameScene);

  // set scene switch for splash screen
  splashScreen->SetSwitchToScene(gameSceneID);

  // set initial scene
  sceneStateMachine.SwitchTo(splashScreenID);

  // initialize timer
  deltaTime = clock.restart().asSeconds();
}

void Game::Update() {
  // Handle window events
  window.Update();

  // update scene
  sceneStateMachine.Update(deltaTime);
}

void Game::LateUpdate() {
  // update state based on previous events
  sceneStateMachine.LateUpdate(deltaTime);
}

void Game::Draw() {
  // clear the screen
  window.BeginDraw();

  // draw objects
  sceneStateMachine.Draw(window);

  // update screen with new drawings
  window.EndDraw();
}

bool Game::IsRunning() const {
  // return state of current window, if window is closed, game is closed
  return window.IsOpen();
}

void Game::CalculateDeltaTime() {
  // calculate time of one game loop
  deltaTime = clock.restart().asSeconds();
}

void Game::ProcessInput() {
  // grab key inputs
  sceneStateMachine.ProcessInput();
}