#include "CDirection.hpp"

#include "Object.hpp"

CDirection::CDirection(Object* owner)
    : Component(owner), currentDir(FacingDirection::None) {}

void CDirection::Awake() { velocity = owner->GetComponent<CVelocity>();
assert(velocity != nullptr); }

FacingDirection CDirection::Get() {
  const sf::Vector2f& currentVel = velocity->Get();

  /**
   * TODO current direction will be determined based on where
   * the opponent character is. Also direction wont change if
   * the a character has momentum. But maybe can change on
   * an updated air action?
   */
  if (currentVel.x != 0.f) {
    if (currentVel.x < 0) {
      currentDir = FacingDirection::Left;
    } else {
      currentDir = FacingDirection::Right;
    }
  }
  return currentDir;
}

void CDirection::Set(FacingDirection direction){
  currentDir = direction;
}