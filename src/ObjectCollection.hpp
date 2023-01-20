#ifndef OBJECTCOLLECTION_HPP
#define OBJECTCOLLECTION_HPP

#include <memory>
#include <vector>

#include "Object.hpp"
#include "SCollidable.hpp"
#include "SDrawable.hpp"

class ObjectCollection {
 public:
  void Add(std::shared_ptr<Object> object);
  void Update(float deltaTIme);
  void LateUpdate(float deltaTime);
  void Draw(Window& window);
  void ProcessNewObjects();
  void ProcessRemovals();

 private:
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Object>> newObjects;
  SDrawable drawables;
  SCollidable collidables;
};
#endif