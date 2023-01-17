#ifndef ccollider_hpp
#define ccollider_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

#include "Component.hpp"

// TODO make simliar enum for move attributes, such as air invuln, strike
// invuln, airborne, etc...
// This will probably be a class of it's own, but it will probably have a
// simialiar design and system to how CollisionLayers will work
enum class CollisionLayer { None, Player, Throw, HitBox, HurtBox };
struct Manifold {
  bool colliding = false;
  const sf::FloatRect* intersects;
};

class CCollider : public Component {
 public:
  CCollider(Object* owner);
  ~CCollider();
  virtual Manifold Intersects(std::shared_ptr<CCollider> intersects) = 0;
  virtual void ResolveOverlap(const Manifold& m) = 0;
  CollisionLayer GetLayer() const;
  void SetLayer(CollisionLayer layer);

 private:
  CollisionLayer layer;
};

#endif