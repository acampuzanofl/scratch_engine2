#ifndef cvelocity_hpp
#define cvelocity_hpp
#include <math.h>

#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "Object.hpp"

class CVelocity : public Component {
 public:
  CVelocity(Object* owner);
  void Update(float deltatime) override;
  void Set(const sf::Vector2f& vel);
  void Set(float x, float y);
  const sf::Vector2f& Get() const;
  void SetWeight(float weight);

 private:
  void ClampVelocity();
  sf::Vector2f velocity;
  sf::Vector2f maxVelocity;
  float weight;
};
#endif
