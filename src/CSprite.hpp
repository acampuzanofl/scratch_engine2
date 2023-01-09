#ifndef CSPRITE_HPP
#define CSPRITE_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "CTransform.hpp"
#include "Component.hpp"
#include "ResourceAllocator.hpp"
#include "Window.hpp"

// CSprite provides a drawable sprite for the owner
// Csprite is responisble for pulling the correct sprite from an atlas
// and positioning the sprite on the screen
class CSprite : public Component {
public:
  CSprite(Object *owner);

  // load a sprite from file
  void Load(const std::string &filePath);
  void Load(int id);
  void SetTextureAllocator(ResourceAllocator<sf::Texture> *allocator);
  void LateUpdate(float deltaTime) override;
  void Draw(Window &window) override;
  void SetTextureRect(int x, int y, int width, int height);
  void SetTextureRect(const sf::IntRect &rect);
  void SetRotation(float rotation);

private:
  ResourceAllocator<sf::Texture> *allocator;
  sf::Sprite sprite;
  int currentTextureId;
};

#endif