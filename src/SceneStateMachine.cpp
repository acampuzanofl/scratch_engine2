#include "SceneStateMachine.hpp"

#include <utility>

SceneStateMachine::SceneStateMachine() : scenes(0), currentScene(0){};

void SceneStateMachine::ProcessInput() {
  if (currentScene) {
    currentScene->ProcessInput();
  }
}

void SceneStateMachine::Update(float deltaTime) {
  if (currentScene) {
    currentScene->Update(deltaTime);
  }
}

void SceneStateMachine::LateUpdate(float deltaTime) {
  if (currentScene) {
    currentScene->LateUpdate(deltaTime);
  }
}

void SceneStateMachine::Draw(Window& window) {
  if (currentScene) {
    currentScene->Draw(window);
  }
}

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene) {
  auto inserted = scenes.insert(std::make_pair(currentSceneID, scene));
  currentSceneID++;
  inserted.first->second->OnCreate();
  return currentSceneID - 1;
}

void SceneStateMachine::Remove(unsigned int id) {
  auto scene = scenes.find(id);
  if (scene != scenes.end()) {
    if (currentScene == scene->second) {
      currentScene = nullptr;
    }
    scene->second->OnDestroy();
    scenes.erase(scene);
  }
}

void SceneStateMachine::SwitchTo(unsigned int id) {
  auto scene = scenes.find(id);
  if (scene != scenes.end()) {
    if (currentScene == scene->second) {
      currentScene->OnDeactivate();
    }
    currentScene = scene->second;
    currentScene->OnActivate();
  }
}