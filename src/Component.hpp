#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Window.hpp"

class Object;

class Component {
 public:
  Component(Object* owner) : owner(owner) {}
  virtual void Awake(){};
  virtual void Start(){};
  virtual void Update(float deltaTime){};
  virtual void LateUpdate(float deltaTime){};
  virtual void Draw(Window& window){};

 protected:
  Object* owner;
};

#endif