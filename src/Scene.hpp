#ifndef SCENE_HPP
#define SCENE_HPP
#include "Window.hpp"

class Scene {
 public:
  // when scene is created
  virtual void OnCreate() = 0;
  // when scene is destroyed
  virtual void OnDestroy() = 0;
  // when transition to new scene
  virtual void OnActivate() = 0;
  // when transition away from current scene
  virtual void OnDeactivate(){};
  virtual void ProcessInput(){};
  virtual void Update(float /*deltaTime*/){};
  virtual void LateUpdate(float /*deltaTime*/){};
  virtual void Draw(Window& /*window*/){};
};
#endif
