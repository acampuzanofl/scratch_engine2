#include "CTransform.hpp"

#include <SFML/System/Vector2.hpp>

#include "Component.hpp"

CTransform::CTransform(Object* owner)
    : Component(owner), position(0.f, 0.f), isStaticTransform(false) {}
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
void CTransform::SetStatic(bool isStatic) { isStaticTransform = isStatic; }
bool CTransform::isStatic() const { return isStaticTransform; }
