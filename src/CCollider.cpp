#include "CCollider.hpp"

#include "Component.hpp"

CCollider::CCollider(Object* owner)
    : Component(owner), layer(CollisionLayer::None) {}

CCollider::~CCollider() {}

CollisionLayer CCollider::GetLayer() const { return layer; }
void CCollider::SetLayer(CollisionLayer layer) { this->layer = layer; }
Object* CCollider::GetOwner() const { return this->owner; }
