#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include "CDrawable.hpp"
#include "CTransform.hpp"
#include "Component.hpp"

class Object {
 public:
  Object();
  // awake is called when an object is created. Used to ensure
  // required components are present
  void Awake();

  // start is called after awake, used to initialize variables
  void Start();
  void Update(float deltaTime);
  void LateUpdate(float deltaTime);
  void Draw(Window& window);
  bool IsQueuedForRemoval();
  void QueueForRemoval();

  template <typename T>
  std::shared_ptr<T> AddComponent() {
    // make sure we only add components derived from the Component class
    static_assert(std::is_base_of<Component, T>::value,
                  "class must be derived from Component");
    // check if component already exists
    for (auto& existingComponent : components) {
      if (std::dynamic_pointer_cast<T>(existingComponent)) {
        return std::dynamic_pointer_cast<T>(existingComponent);
      }
    }

    // if the object does not have this component, create it and add it
    std::shared_ptr<T> newComponent = std::make_shared<T>(this);
    components.push_back(newComponent);

    // check if the component is a cdrawable component
    if (std::dynamic_pointer_cast<CDrawable>(newComponent)) {
      drawable = std::dynamic_pointer_cast<CDrawable>(newComponent);
    }
    return newComponent;
  }

  std::shared_ptr<CDrawable> GetDrawable();

  template <typename T>
  std::shared_ptr<T> GetComponent() {
    // check if component already exists
    for (auto& existingComponent : components) {
      if (std::dynamic_pointer_cast<T>(existingComponent)) {
        return std::dynamic_pointer_cast<T>(existingComponent);
      }
    }
    return nullptr;
  }
  std::shared_ptr<CTransform> transform;

 private:
  std::vector<std::shared_ptr<Component>> components;
  std::shared_ptr<CDrawable> drawable;
  bool queuedForRemoval;
};

#endif