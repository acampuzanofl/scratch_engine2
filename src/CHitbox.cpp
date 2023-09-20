#include "CHitbox.hpp"

#include <memory>

#include "CBoxCollider.hpp"
#include "Object.hpp"

CHitbox::CHitbox(Object* owner) : CBoxCollider(owner) {}
void CHitbox::Awake() {}
void CHitbox::Start() {}
void CHitbox::Update(float deltaTime) { SpawnHitbox(); }
void CHitbox::SetObjectCollection(ObjectCollection* objects) {
  this->objects = objects;
}
void CHitbox::SpawnHitbox() {
  std::shared_ptr<Object> hitbox = std::make_shared<Object>(owner->context);
  hitbox->transform->SetPosition(owner->transform->GetPosition());
  objects->Add(hitbox);
}