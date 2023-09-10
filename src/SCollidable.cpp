#include "SCollidable.hpp"

#include <SFML/System/Vector2.hpp>
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
  /**
   *  here is where i would add/update collidables into my collision data struct
   *  currently i do not have one, so im leaving it blank
   *  TODO: create a data struct to handle optimizing collision detection
   *  apperently adding collidables to the data struct in this step is a
   *  performance loss dynamically updating the data struct is the best
   *  implementation. TODO: implement the easier one of the too, dynamic or add
   *  it here
   */
  Resolve();
}

void SCollidable::Resolve() {
  for (const auto& maps : collidables) {
    /**
     *  check what the layer collides with
     *  if the layer collides with nothing then exit
     */
    if (maps.first == CollisionLayer::None) {
      continue;
    }

    /**
     * check if layers can collide with each other. This will always be true
     * for now since we are only checking for collisions with objects that are
     * within the same layer. the intention is that each object will have a
     * collision mask to determine what it's allowed to collide with. still
     * determing whats the best way to implement that system
     */

    /**
     * loop through all the collidables in a layer
     */
    for (const auto& collidable : /*collidables*/ maps.second) {
      /**
       *  we will temporarily loop through all objects on the same layer and
       *  check if we are colliding with any of them
       */
      std::vector<std::shared_ptr<CBoxCollider>> collisions = maps.second;
      for (const auto& collision : collisions) {
        /**
         *  perform a check to make sure we do not resolve collisions between
         *  the same object
         *  TODO change names of instance ID, also make instance id private and
         *  create a getter. Also make transorm privatea and make a getter
         */

        // draw collision boxes
        Debug::DrawRect(collision->GetCollidable());
        Debug::DrawRect(collidable->GetCollidable());

        if (collidable->GetOwner()->instanceId->GetInstanceId() ==
            collision->GetOwner()->instanceId->GetInstanceId()) {
          continue;
        }

        /**
         * We check if the layers are allowed to collide, This should be
         * implemented as a bit mask. But for now they are just enums
         */
        int layersCollide =
            ((int)collidable->GetLayer() & (int)collision->GetLayer());
        if (layersCollide) {
          Manifold m = collidable->Intersects(collision);
          if (m.colliding) {
            /**
             * We check if the collision is moving, and if it is we resolve the
             * collision on the collidable. This is a bad way to implement this,
             * but it does simulate the behavior i want. The behavior i want is
             * for the collision to resolve differently depending on which
             * object is moving. The problem is that this doesnt handle the case
             * for when both objects are moving correctly. they behavior that i
             * expect is both objects should cause a collision to occur which
             * triggers each others resolveoverlap. What actually occurs is that
             * only one resolveoverlap occurs, and its the one that was added to
             * the collidables list last whos overlap gets resolved. TODO: find
             * a way to resolve collisions between to objects simulaneuosly.
             */
            if (collision->GetOwner()->transform->GetVelocity().x != 0) {
              collidable->ResolveOverlap(m);
            } else {
              /**
               * TODO: im not sure if
               * different types of collisions need to be resolved based on
               * what type of layer is colliding. Maybe a switch case? or
               * callbacks? to enable handling collisions from different layers
               */
            }
          }
        }
      }
    }
  }
}