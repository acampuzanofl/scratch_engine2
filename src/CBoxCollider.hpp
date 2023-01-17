#ifndef cboxcollider_hpp
#define cboxcollider_hpp

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "CCollider.hpp"
#include "Component.hpp"

class CBoxCollider : public CCollider {
 public:
  CBoxCollider(Object* owner);
  Manifold Intersects(std::shared_ptr<CCollider> intersects) override;
  void ResolveOverlap(const Manifold& m) override;
  void SetCollidable(const sf::FloatRect& rect);
  const sf::FloatRect& GetCollidable();

 private:
  void SetPosition();
  sf::FloatRect AABB;
  sf::Vector2f offset;
};

#endif