#ifndef ccamera_hpp
#define ccamera_hpp
#include "Component.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "Window.hpp"

class CCamera : public Component {
 public:
  CCamera(Object* owner);
  void LateUpdate(float deltaTime) override;
  void SetWindow(Window* gameWindow);
  /**
   * TODO This is tempory input for testing
   * camera zooming
   */
  void SetInput(Input* input);
  void SetCameraZoom(Window& window, float zoom);

 private:
  Window* window;
  /**
   * TODO This is tempory input for testing
   * camera zooming
   */
  Input* input;
};

#endif