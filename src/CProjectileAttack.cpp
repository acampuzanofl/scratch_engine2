#include "CProjectileAttack.hpp"

#include "Object.hpp"

CProjectileAttack::CProjectileAttack(Object* owner) : Component(owner) {}
std::unordered_map<FacingDirection, sf::IntRect> CProjectileAttack::textureDirectionBindings = {};

void CProjectileAttack::Awake() {
  animation = owner->GetComponent<CAnimation>();
  direction = owner->GetComponent<CDirection>();

}

void CProjectileAttack::Start() {
  projectileTextureID = owner->context->textureAllocator->Add(
      owner->context->workingDir->Get() + "LPC/Weapons/arrow.png");
  textureDirectionBindings.emplace(FacingDirection::Left, sf::IntRect({64, 0}, {64, 64}));
  textureDirectionBindings.emplace(FacingDirection::Right, sf::IntRect({192, 0}, {64, 64}));
}

void CProjectileAttack::Update(float deltaTime) {
  if (owner->context->input->IsKeyDown(Input::Key::D)) {
    SpawnProjectile();
    animation->SetAnimationState(AnimationState::ProjectileLoop);
  } else if (owner->context->input->IsKeyUp(Input::Key::D)) {
    animation->SetAnimationState(AnimationState::Idle);
  }
}

void CProjectileAttack::SpawnProjectile() {
  std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);

  projectile->transform->SetPosition(owner->transform->GetPosition());

	// Get the current facing direction.
  FacingDirection currentDir = direction->Get();

  auto projSprite = projectile->AddComponent<CSprite>();
  projSprite->Load(projectileTextureID);
  projSprite->SetDrawLayer(DrawLayer::Entities);
  projSprite->SetSortOrder(100);

	// Use the direction to set the texture rect.
    projSprite->SetTextureRect(textureDirectionBindings.at(direction->Get()));

  owner->context->objects->Add(projectile);
}