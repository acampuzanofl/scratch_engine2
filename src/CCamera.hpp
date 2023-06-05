#ifndef ccamera_hpp
#define ccamera_hpp
#include "Component.hpp"
#include "Object.hpp"
#include "Window.hpp"

class CCamera : public Component {
 public:
  CCamera(Object* owner);
  void LateUpdate(float deltaTime) override;
  void SetWindow(Window* gameWindow);

 private:
  Window* window;
};

#endif