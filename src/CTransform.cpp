#include "CTransform.hpp"

#include <SFML/System/Vector2.hpp>
#include <cassert>

#include "Component.hpp"
#include "Debug.hpp"

CTransform::CTransform(Object* owner)
    : Component(owner), position(0.f, 0.f), weight(50) {}
void CTransform::SetPosition(float x, float y) {
  position.x = x;
  position.y = y;
}

void CTransform::SetPosition(const sf::Vector2f& pos) { position = pos; }
void CTransform::AddPosition(float x, float y) {
  position.x += x;
  position.y += y;
}

void CTransform::AddPosition(const sf::Vector2f& pos) { position += pos; }
void CTransform::SetX(float x) { position.x = x; }
void CTransform::SetY(float y) { position.y = y; }
void CTransform::AddX(float x) { position.x += x; }
void CTransform::AddY(float y) { position.y += y; }
const sf::Vector2f& CTransform::GetPosition() const { return position; }
float CTransform::GetX() { return position.x; }
float CTransform::GetY() { return position.y; }
void CTransform::SetVelocity(const sf::Vector2f& velocity) {
  this->velocity = velocity;
}
const sf::Vector2f& CTransform::GetVelocity() const { return velocity; }
void CTransform::SetWeight(float weight) { this->weight = weight; }
void CTransform::Update(float dt) {
  position += velocity * dt;

  /**
   * TODO: if weight is too big velcocity can be negative
   * this results in undefined behavior. For now, as long as
   * weight is < 60, it seems to be fine. Turns out the behavior
   * causes the position/velocity to oscilate between positive and negative
   * this needs to be fixed properly.
   */
  assert(weight < 60);
  velocity *= 1.f - weight * dt;
}
void CTransform::SetMoveSpeed(int moveSpeed) { this->moveSpeed = moveSpeed; }
