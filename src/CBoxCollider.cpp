#include "CBoxCollider.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include <optional>

#include "CCollider.hpp"
#include "Debug.hpp"
#include "Object.hpp"

CBoxCollider::CBoxCollider(Object* owner)
    : CCollider(owner), offset(sf::Vector2f(0.f, 0.f)) {}

void CBoxCollider::SetCollidable(const sf::FloatRect& rect) {
  AABB = rect;
  SetPosition();
}

const sf::FloatRect& CBoxCollider::GetCollidable() {
  SetPosition();
  return AABB;
}

/**
 * Set position gets called every time a check for intersects occurs. It also
 * gets called during resolve overlap. This means that the collider will get its
 * position updated during collision checking.
 */

void CBoxCollider::SetPosition() {
  const sf::Vector2f& pos = owner->transform->GetPosition();
  AABB.position = sf::Vector2f(pos.x - (AABB.size.x / 2) + offset.x,
                               pos.y - (AABB.size.y / 2) + offset.y);
}

Manifold CBoxCollider::Intersects(std::shared_ptr<CCollider> intersects) {
  Manifold m;
  m.colliding = false;

  std::shared_ptr<CBoxCollider> boxCollider =
      std::dynamic_pointer_cast<CBoxCollider>(intersects);

  if (boxCollider) {
    const sf::FloatRect& rect1 = GetCollidable();
    const sf::FloatRect& rect2 = boxCollider->GetCollidable();

    // Use findIntersection to get overlapping area
    std::optional<sf::FloatRect> intersection = rect1.findIntersection(rect2);
    if (intersection.has_value()) {
      m.colliding = true;
      m.intersects = new sf::FloatRect(intersection.value()); // Use the overlapping rect
    }
  }

  return m;
}

void CBoxCollider::ResolveOverlap(const Manifold& m) {
  auto transform = owner->transform;

  const sf::FloatRect& rect1 = GetCollidable();
  const sf::FloatRect* rect2 = m.intersects;
  float resolve = 0;
  float xDiff = (rect1.position.x + (rect1.size.x * 0.5f)) -
                (rect2->position.x + (rect2->size.x * 0.5f));
  float yDiff = (rect1.position.y + (rect1.size.y * 0.5f)) -
                (rect2->position.y + (rect2->size.y * 0.5f));
  if (fabs(xDiff) > fabs(yDiff)) {
    if (xDiff > 0)  // Colliding on the left.
    {
      // We add a positive x value to move the object to the right.
      resolve = (rect2->position.x + rect2->size.x) - rect1.position.x;
    } else  // Colliding on the right.
    {
      // We add a negative x value to move the object to the left.
      resolve = -(rect1.position.x + rect1.size.x - rect2->position.x);
    }
    transform->AddPosition(resolve, 0);
  } else {
    if (yDiff > 0)  // Colliding above.
    {
      // We add a positive y value to move the object down.
      resolve = (rect2->position.y + rect2->size.y) - rect1.position.y;
    } else  // Colliding below
    {
      // We add a negative y value to move the object up.
      resolve = -(rect1.position.y + rect1.size.y - rect2->position.y);
    }
    transform->AddPosition(0, resolve);
  }
}

void CBoxCollider::SetOffset(const sf::Vector2f& offset) {
  this->offset = offset;
}
void CBoxCollider::SetOffset(float x, float y) {
  offset.x = x;
  offset.y = y;
}
void CBoxCollider::SetSize(const sf::Vector2f& size) {
  AABB.size = size;
}
void CBoxCollider::SetSize(float width, float height) {
  AABB.size = sf::Vector2f(width, height);
}

const sf::Vector2f& CBoxCollider::GetOffset() { return offset; }
