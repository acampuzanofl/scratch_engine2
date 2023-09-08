#include "CVelocity.hpp"

#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "Object.hpp"

CVelocity::CVelocity(Object* owner)
    : Component(owner), maxVelocity(500.f, 500.f), weight(10) {}

void CVelocity::Update(float deltatime) {
  owner->transform->AddPosition(velocity * deltatime);
  Set(velocity - (velocity * deltatime * this->weight));
  ClampVelocity();
}

void CVelocity::Set(const sf::Vector2f& vel) {
  velocity = vel;
  ClampVelocity();
}

void CVelocity::Set(float x, float y) {
  velocity.x = x;
  velocity.y = y;
  ClampVelocity();
}

const sf::Vector2f& CVelocity::Get() const { return velocity; }

void CVelocity::ClampVelocity() {
  if (fabs(velocity.x) > maxVelocity.x) {
    if (velocity.x > 0.f) {
      velocity.x = maxVelocity.x;
    } else {
      velocity.x = -maxVelocity.x;
    }
  }
  if (fabs(velocity.y) > maxVelocity.y) {
    if (velocity.y > 0.f) {
      velocity.y = maxVelocity.y;
    } else {
      velocity.y = -maxVelocity.y;
    }
  }
}

void CVelocity::SetWeight(float weight) { this->weight = weight; }