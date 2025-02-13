#ifndef scollidable_hpp
#define scollidable_hpp

#include <map>
#include <memory>
#include <vector>

#include "Bitmask.hpp"
#include "CBoxCollider.hpp"
#include "CCollider.hpp"
#include "Object.hpp"

class SCollidable {
 public:
  SCollidable();
  void Add(std::vector<std::shared_ptr<Object>>& objects);
  void ProcessRemovals();
  void Update();
  void LateUpdate();

 private:
  void ResolveCollisions();
  void DetectCollisions();
  std::map<CollisionLayer, std::vector<std::shared_ptr<CBoxCollider>>> collidables;
};

#endif