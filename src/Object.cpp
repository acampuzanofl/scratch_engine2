#include "Object.hpp"

#include <memory>

#include "CDrawable.hpp"
#include "CTransform.hpp"

Object::Object() : queuedForRemoval(false) {
  transform = AddComponent<CTransform>();
}

void Object::QueueForRemoval() { queuedForRemoval = true; }
bool Object::IsQueuedForRemoval() { return queuedForRemoval; }

void Object::Awake() {
  for (int i = components.size() - 1; i >= 0; i--) {
    components[i]->Awake();
  }
}

void Object::Start() {
  for (int i = components.size() - 1; i >= 0; i--) {
    components[i]->Awake();
  }
}

void Object::Update(float deltaTime) {
  for (int i = components.size() - 1; i >= 0; i--) {
    components[i]->Update(deltaTime);
  }
}

void Object::LateUpdate(float deltaTime) {
  for (int i = components.size() - 1; i >= 0; i--) {
    components[i]->LateUpdate(deltaTime);
  }
}

void Object::Draw(Window& window) {
  for (int i = components.size() - 1; i >= 0; i--) {
    drawable->Draw(window);
  }
}

std::shared_ptr<CDrawable> Object::GetDrawable() { return drawable; }