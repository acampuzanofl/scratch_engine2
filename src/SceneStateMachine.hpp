#ifndef SCENESTATEMACHINE_HPP
#define SCENESTATEMACHINE_HPP

#include <memory>
#include <unordered_map>

#include "Scene.hpp"
#include "Window.hpp"

class SceneStateMachine {
 public:
  SceneStateMachine();
  void ProcessInput();
  void Update(float deltaTime);
  void LateUpdate(float deltaTime);
  void Draw(Window& window);

  // Adds a scene
  unsigned int Add(std::shared_ptr<Scene> scene);

  // transitions to a scene
  void SwitchTo(unsigned int id);

  // removes scene
  void Remove(unsigned int id);

 private:
  // contains all the scenes and their respective ids
  std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
  std::shared_ptr<Scene> currentScene;
  unsigned int currentSceneID;
};

#endif