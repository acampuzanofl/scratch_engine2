#ifndef CProjectileAttack_hpp
#define CProjectileAttack_hpp

#include "CAnimation.hpp"
#include "Component.hpp"
#include "Input.hpp"
#include "ObjectCollection.hpp"
#include "WorkingDirectory.hpp"

class CProjectileAttack : public Component {
 public:
  CProjectileAttack(Object* owner);

  void Awake() override;
  void Start() override;
  void Update(float deltaTime) override;

 private:
  void SpawnProjectile();

  std::shared_ptr<CAnimation> animation;
  int projectileTextureID;
};

#endif /* CProjectileAttack_hpp */