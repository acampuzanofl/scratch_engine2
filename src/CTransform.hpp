#ifndef CTRANSFORM_HPP
#define CTRANSFORM_HPP

#include <SFML/System/Vector2.hpp>
#include <cstdint>

#include "Component.hpp"
class CTransform : public Component {
 public:
  CTransform(Object* owner);
  void SetPosition(float x, float y);
  void SetPosition(const sf::Vector2f& pos);
  void SetVelocity(const sf::Vector2f& vel);
  void AddPosition(float x, float y);
  void AddPosition(const sf::Vector2f& pos);
  const sf::Vector2f& GetPosition() const;
  const sf::Vector2f& GetVelocity() const;
  void Update(float dt);
  void SetX(float x);
  void SetY(float y);
  void AddX(float x);
  void AddY(float y);
  float GetX();
  float GetY();
  void SetWeight(float weight);
  void SetMoveSpeed(int moveSpeed);

 private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  bool isMoving;
  float weight;
  int moveSpeed;
};

#endif