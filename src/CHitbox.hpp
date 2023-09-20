#ifndef chitbox_hpp
#define chitbox_hpp
#include "CBoxCollider.hpp"
#include "Component.hpp"
#include "ObjectCollection.hpp"

class CHitbox : public CBoxCollider {
 public:
  CHitbox(Object* owner);
  void Awake() override;
  void Start() override;
  void Update(float deltaTime) override;
  void SetObjectCollection(ObjectCollection* objects);

 private:
  void SpawnHitbox();
  ObjectCollection* objects;
  int hitboxID;
};
#endif