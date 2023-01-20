#include "SCollidable.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "Bitmask.hpp"
#include "CBoxCollider.hpp"
#include "CCollider.hpp"
#include "Debug.hpp"

SCollidable::SCollidable() {}

void SCollidable::Add(std::vector<std::shared_ptr<Object>>& objects) {
  for (auto o : objects) {
    auto collider = o->GetComponent<CBoxCollider>();
    // orgnizer colliders based on layers
    if (collider) {
      CollisionLayer layer = collider->GetLayer();
      auto it = collidables.find(layer);
      if (it != collidables.end()) {
        collidables[layer].push_back(collider);
      } else {
        // create a new vector for colliders if that layer wasnt already in the
        // map
        std::vector<std::shared_ptr<CBoxCollider>> objs;
        objs.push_back(collider);
        collidables.insert(std::make_pair(layer, objs));
      }
    }
  }
}

void SCollidable::ProcessRemovals() {
  for (auto& layer : collidables) {
    layer.second.erase(
        std::remove_if(layer.second.begin(), layer.second.end(),
                       [](std::shared_ptr<CBoxCollider>& o) {
                         return o->GetOwner()->IsQueuedForRemoval();
                       }),
        layer.second.end());
  }
}

void SCollidable::Update() {
  // here is where i would add collidables into my collision data struct
  // currently i do not have one, so im leaving it blank
  // TODO create a data struct to handle optimizing collision detection
  // apperently adding collidables to the data struct in this step is a
  // performance loss dynamically updating the data struct is the best
  // implementation. TODO implement the easier one of the too, dynamic or add it
  // here
  Resolve();
}

void SCollidable::Resolve() {
  for (auto maps : collidables) {
    // check what the layer collides with
    // if the layer collides with nothing then exit
    if (maps.first == CollisionLayer::None) {
      continue;
    }

    for (auto collidable : maps.second) {
      if (collidable->GetOwner()->transform->isStatic()) {
        continue;
      }
      // we will temporarily loop throuhg all objects on the
      // same layer and check if we are colliding with any of
      // them
      std::vector<std::shared_ptr<CBoxCollider>> collisions = maps.second;
      for (auto collision : collisions) {
        // perform a check to make sure we do not resolve collisions between the
        // same object
        // TODO change names of instance ID, also make instance id private and
        // create a getter. Also make transorm privatea and make a getter
        if (collidable->GetOwner()->instanceId->GetInstanceId() ==
            collision->GetOwner()->instanceId->GetInstanceId()) {
          continue;
        }

        // check if the layers can collide
        // with each other. This will always be true for now since
        // we are only checking for collisions for objects that are within the
        // same layer anyways the intention is that each object will have its
        // own collision mask to determine what it's allowed to collide with.
        // Still determing whats the best way to implement that system

        // debug
        Debug::DrawRect(collision->GetCollidable());
        Debug::DrawRect(collidable->GetCollidable());

        int layersCollide =
            ((int)collidable->GetLayer() & (int)collision->GetLayer());
        if (layersCollide) {
          Manifold m = collidable->Intersects(collision);
          if (m.colliding) {
            if (collision->GetOwner()->transform->isStatic()) {
              collidable->ResolveOverlap(m);
            } else {
              // TODO i just copied this implementatoin
              // im not sure i will have "Static" objects
              // different types of collisions need to be resolved based on what
              // type of layer is colliding. Maybe a switch case? or callbacks?
              // to enable handling collisions from different layers
              collidable->ResolveOverlap(m);
            }
          }
        }
      }
    }
  }
}