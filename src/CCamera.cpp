#include "CCamera.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "Object.hpp"

CCamera::CCamera(Object* owner) : Component(owner) {}
void CCamera::LateUpdate(float deltaTime) {
  if (window) {
    sf::View view = window->GetView();
    const sf::Vector2f& targerPos = owner->transform->GetPosition();
    // TODO remove hard coded value of y
    view.setCenter(targerPos.x, 500);
    window->SetView(view);
  }

  /**
   * TODO
   * This is a tempory test for zoom feature
   * i am implementing this as a keyboard command for debugging
   * zooming should be handled automatically based on the positions
   * of each of the characters in the scene. The scene will be responsible
   * for determing how to move the ccamera and when to zoom
   */
  if (input->IsKeyPressed(Input::Key::Zoomin)) {
    SetCameraZoom(*window, 1.1f);
  } else if (input->IsKeyPressed(Input::Key::Zoomout)) {
    SetCameraZoom(*window, .9f);
  }
}

void CCamera::SetWindow(Window* gameWindow) { window = gameWindow; }
void CCamera::SetInput(Input* input) { this->input = input; }
void CCamera::SetCameraZoom(Window& window, float zoom) {
  sf::View view = window.GetView();
  view.zoom(zoom);
  window.SetView(view);
}