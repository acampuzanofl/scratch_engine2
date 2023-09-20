#include "CProjectileAttack.hpp"

#include "Object.hpp"

CProjectileAttack::CProjectileAttack(Object* owner) : Component(owner) {}

void CProjectileAttack::Awake() {
  animation = owner->GetComponent<CAnimation>();
}

void CProjectileAttack::Start() {
  projectileTextureID = owner->context->textureAllocator->Add(
      owner->context->workingDir->Get() + "LPC/Weapons/arrow.png");
}

void CProjectileAttack::Update(float deltaTime) {
  if (owner->context->input->IsKeyDown(Input::Key::D)) {
    SpawnProjectile();
    animation->SetAnimationState(AnimationState::Projectile);
  } else if (owner->context->input->IsKeyUp(Input::Key::D)) {
    animation->SetAnimationState(AnimationState::Idle);
  }
}

void CProjectileAttack::SpawnProjectile() {
  std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);

  projectile->transform->SetPosition(owner->transform->GetPosition());

  auto projSprite = projectile->AddComponent<CSprite>();
  projSprite->Load(projectileTextureID);
  projSprite->SetDrawLayer(DrawLayer::Entities);
  projSprite->SetSortOrder(100);

  owner->context->objects->Add(projectile);
}