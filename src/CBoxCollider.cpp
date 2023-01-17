#include "CBoxCollider.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>

#include "CCollider.hpp"
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

void CBoxCollider::SetPosition() {
  const sf::Vector2f& pos = owner->transform->GetPosition();
  AABB.left = pos.x - (AABB.width / 2) + offset.x;
  AABB.top = pos.y - (AABB.height / 2) + offset.y;
}

Manifold CBoxCollider::Intersects(std::shared_ptr<CCollider> intersects) {
  Manifold m;
  m.colliding = false;
  std::shared_ptr<CBoxCollider> boxCollider =
      std::dynamic_pointer_cast<CBoxCollider>(intersects);
  if (boxCollider) {
    const sf::FloatRect& rect1 = GetCollidable();
    const sf::FloatRect& rect2 = boxCollider->GetCollidable();
    if (rect1.intersects(rect2)) {
      m.colliding = true;
      m.intersects = &rect2;
    }
  }
  return m;
}

void CBoxCollider::ResolveOverlap(const Manifold& m) {
  auto transform = owner->transform;
  if (transform->isStatic()) {
    return;
  }
  const sf::FloatRect& rect1 = GetCollidable();
  const sf::FloatRect* rect2 = m.intersects;
  float resolve = 0;
  float xDiff = (rect1.left + (rect1.width * 0.5f)) -
                (rect2->left + (rect2->width * 0.5f));
  float yDiff = (rect1.top + (rect1.height * 0.5f)) -
                (rect2->top + (rect2->height * 0.5f));
  if (fabs(xDiff) > fabs(yDiff)) {
    if (xDiff > 0)  // Colliding on the left.
    {
      // We add a positive x value to move the object to the right.
      resolve = (rect2->left + rect2->width) - rect1.left;
    } else  // Colliding on the right.
    {
      // We add a negative x value to move the object to the left.
      resolve = -((rect1.left + rect1.width) - rect2->left);
    }
    transform->AddPosition(resolve, 0);
  } else {
    if (yDiff > 0)  // Colliding above.
    {
      // We add a positive y value to move the object down.
      resolve = (rect2->top + rect2->height) - rect1.top;
    } else  // Colliding below
    {
      // We add a negative y value to move the object up.
      resolve = -((rect1.top + rect1.height) - rect2->top);
    }
    transform->AddPosition(0, resolve);
  }
}
