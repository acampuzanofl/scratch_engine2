#include "ObjectCollection.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

#include "Window.hpp"

void ObjectCollection::Update(float deltaTIme) {
  for (auto& o : objects) {
    o->Update(deltaTIme);
  }
  collidables.Update();
}

void ObjectCollection::LateUpdate(float deltaTIme) {
  for (auto& o : objects) {
    o->LateUpdate(deltaTIme);
  }
}

void ObjectCollection::Draw(Window& window) { drawables.Draw(window); }

void ObjectCollection::Add(std::shared_ptr<Object> object) {
  newObjects.push_back(object);
}

void ObjectCollection::ProcessNewObjects() {
  if (newObjects.size() > 0) {
    for (const auto& o : newObjects) {
      o->Awake();
    }
    for (const auto& o : newObjects) {
      o->Start();
    }
    objects.insert(objects.end(), newObjects.begin(), newObjects.end());
    drawables.Add(newObjects);
    collidables.Add(newObjects);
    newObjects.clear();
  }
}

void ObjectCollection::ProcessRemovals() {
  auto it = std::remove_if(
      objects.begin(), objects.end(),
      [](std::shared_ptr<Object>& o) { return o->IsQueuedForRemoval(); });
  if (it != objects.end()) {
    objects.erase(it, objects.end());
    drawables.ProcessRemovals();
    collidables.ProcessRemovals();
  }
}