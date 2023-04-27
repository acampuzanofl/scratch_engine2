#include "CTransform.hpp"

#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "Debug.hpp"

CTransform::CTransform(Object* owner)
    : Component(owner), position(0.f, 0.f), weight(10) {}
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
  velocity *= 1.f - weight * dt;
  Debug::Log("velocity: %f %f", velocity.x, velocity.y);
}
void CTransform::SetMoveSpeed(int moveSpeed) { this->moveSpeed = moveSpeed; }
