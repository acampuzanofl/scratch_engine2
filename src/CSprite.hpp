#ifndef CSPRITE_HPP
#define CSPRITE_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>

#include "Animation.hpp"
#include "CDrawable.hpp"
#include "CTransform.hpp"
#include "Component.hpp"
#include "ResourceAllocator.hpp"
#include "SpriteMap.hpp"
#include "Window.hpp"

// CSprite provides a drawable sprite for the owner
// Csprite is responisble for pulling the correct sprite from an atlas
// and positioning the sprite on the screen
class CSprite : public Component, public CDrawable {
 public:
  CSprite(Object *owner);

  // load a sprite from file
  void Load(const std::string &textureFilePath);
  void Load(int textureid);
  void Load(const std::string &textureFilePath,
            const std::string &spriteMapFilePath);
  void Load(int textureid, int spriteMapid);
  void SetAllocator(ResourceAllocator<sf::Texture> *allocator);
  void SetAllocator(ResourceAllocator<SpriteMap> *allocator);
  void LateUpdate(float deltaTime) override;
  void Draw(Window &window) override;
  void SetTextureRect(int x, int y, int width, int height);
  void SetTextureRect(const sf::IntRect &rect);
  std::shared_ptr<Animation> CreateAnimationFromSpriteMap(
      const std::string &animationName, float animationSpeed);

  sf::Sprite GetSprite() const;
  bool ContinueToDraw() const override;

 private:
  ResourceAllocator<sf::Texture> *textureAllocator;
  ResourceAllocator<SpriteMap> *spriteMapAllocator;
  sf::Sprite sprite;
  int currentTextureId;
  int currentSpriteMapid;
};

#endif