#include "CCamera.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "Object.hpp"

CCamera::CCamera(Object* owner) : Component(owner) {}
void CCamera::LateUpdate(float deltaTime) {
  if (window) {
  sf:
    sf::View view = window->GetView();
    const sf::Vector2f& targerPos = owner->transform->GetPosition();
    // TODO remove hard coded value of y
    view.setCenter(targerPos.x, 500);
    window->SetView(view);
  }
}

void CCamera::SetWindow(Window* gameWindow) { window = gameWindow; }