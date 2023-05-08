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
  void SetOffset(const sf::Vector2f& offset);
  void SetOffset(float x, float y);
  const sf::Vector2f& GetOffset();
  void SetSize(const sf::Vector2f& size);
  void SetSize(float width, float height);

 private:
  void SetPosition();
  sf::FloatRect AABB;
  sf::Vector2f offset;
};

#endif