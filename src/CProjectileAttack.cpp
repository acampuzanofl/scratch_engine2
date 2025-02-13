#include "CProjectileAttack.hpp"

#include "Object.hpp"

CProjectileAttack::CProjectileAttack(Object* owner) : Component(owner) {}

void CProjectileAttack::Start() {
  projectile = std::make_shared<Object>(owner->context);

  direction = owner->GetComponent<CDirection>();

  auto sprite = projectile->AddComponent<CSprite>();
    sprite->Load(
      owner->context->workingDir->Get() + "characters/Fireball/FireballSpritesheet/FireballSpritesheet.png",
      owner->context->workingDir->Get() + "characters/Fireball/FireballSpritesheet/FireballSpritesheet.json");
  projectile->transform->SetPosition(owner->transform->GetPosition());

  projectile->AddComponent<CDirection>();
  projectile->AddComponent<CVelocity>();
  animation = projectile->AddComponent<CAnimation>();
  std::shared_ptr<Animation> fireballLoop =
      sprite->CreateAnimationFromSpriteMap("FireballLoop", .05f, true);
  std::shared_ptr<Animation> fireballEnd =
      sprite->CreateAnimationFromSpriteMap("FireballEnd", .05f, true);
  animation->AddAnimation(AnimationState::ProjectileLoop, fireballLoop);
  animation->AddAnimation(AnimationState::ProjectileEnd, fireballEnd);

  auto owneranimation = owner->GetComponent<CAnimation>();
  auto battack = owneranimation->GetAnimationByState(AnimationState::B);
  battack->AddFrameCallback(3, [this]() {
    SpawnProjectile();
  });
}

void CProjectileAttack::Update(float deltaTime) {

  /**
   * TODO: temporary hot fix to prevent a busy update loop. Exit early if lifeTime has not been set
   */
  if( lifeTime == 0.f){
    return;
  } else if (currenTime > lifeTime)
  {
    lifeTime = 0.f;
    currenTime = 0.f;
    projectile->QueueForRemoval();
  }else{
  currenTime += deltaTime;}
}

void CProjectileAttack::SpawnProjectile() {
  projectile = std::make_shared<Object>(owner->context);

  auto sprite = projectile->AddComponent<CSprite>();
    sprite->Load(
      owner->context->workingDir->Get() + "characters/Fireball/FireballSpritesheet/FireballSpritesheet.png",
      owner->context->workingDir->Get() + "characters/Fireball/FireballSpritesheet/FireballSpritesheet.json");
  projectile->transform->SetPosition(owner->transform->GetPosition());

  projectile->AddComponent<CDirection>();
  animation = projectile->AddComponent<CAnimation>();
  

  auto velocity = projectile->AddComponent<CVelocity>();
  velocity->Set({300,0});
  velocity->SetWeight(1);

	// Get the current facing direction.
  FacingDirection currentDir = direction->Get();
  if (currentDir == FacingDirection::Left){
    projectile->transform->AddX(-150);
  }else if (currentDir == FacingDirection::Right)
  {
        projectile->transform->AddX(150);
  }
  
  std::shared_ptr<Animation> fireballLoop =
      sprite->CreateAnimationFromSpriteMap("FireballLoop", .05f, true);
  std::shared_ptr<Animation> fireballEnd =
      sprite->CreateAnimationFromSpriteMap("FireballEnd", .05f, true);
  animation->AddAnimation(AnimationState::ProjectileLoop, fireballLoop);
  animation->AddAnimation(AnimationState::ProjectileEnd, fireballEnd);
  animation->SetAnimationState(AnimationState::ProjectileLoop);

  auto fireballcollider = projectile->AddComponent<CBoxCollider>();
  fireballcollider->SetOffset({30,50});
  fireballcollider->SetSize(50, 25);
  fireballcollider->SetLayer(CollisionLayer::Player);

  /**
   * TODO: i dont think this lifetime varaible makes a lot of sense. It seems like a very hacky solution to what im trying to do. Also Update and awake
   * running all the time before i haave "spawned" the projectile seems wrong as well
   */
  lifeTime = 1.f;
  owner->context->objects->Add(projectile);
}
