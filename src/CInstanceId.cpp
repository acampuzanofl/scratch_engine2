#include "CInstanceId.hpp"

#include "Component.hpp"

int CInstanceId::count = 0;
CInstanceId::CInstanceId(Object* owner)
    : Component(owner), instanceId(count++) {}
CInstanceId::~CInstanceId() {}
int CInstanceId::GetInstanceId() const { return instanceId; }