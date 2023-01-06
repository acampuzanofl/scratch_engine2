#include "CSprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

#include "Component.hpp"
#include "Object.hpp"

CSprite::CSprite(Object *owner) : Component(owner), currentTextureId(-1) {}

void CSprite::SetTextureAllocator(ResourceAllocator<sf::Texture> *allocator) {
  this->allocator = allocator;
}

void CSprite::Load(int id) {
  if (id >= 0 && id != currentTextureId) {
    currentTextureId = id;
    std::shared_ptr<sf::Texture> texture = allocator->Get(id);
    sprite.setTexture(*texture);
  }
}

void CSprite::Load(const std::string &filePath) {
  if (allocator) {
    int textureID = allocator->Add(filePath);
    if (textureID >= 0 && textureID != currentTextureId) {
      currentTextureId = textureID;
      std::shared_ptr<sf::Texture> texture = allocator->Get(textureID);
      sprite.setTexture(*texture);
    }
  }
}

void CSprite::LateUpdate(float deltaTime) {
  sf::Vector2f pos = owner->transform->GetPosition();
  const sf::IntRect &spriteBounds = sprite.getTextureRect();
  const sf::Vector2f &spriteScale = sprite.getScale();
  sprite.setPosition(  // set position based on center of sprite
      pos.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x),
      pos.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y));
}

void CSprite::Draw(Window &window) { window.Draw(sprite); }

void CSprite::SetTextureRect(int x, int y, int width, int height) {
  sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void CSprite::SetTextureRect(const sf::IntRect &rect) {
  sprite.setTextureRect(rect);
}

void CSprite::SetPivot(int x, int y) {
  sf::Vector2f position = owner->transform->GetPosition();
  sprite.setPosition(position.x + x, position.y + y);
}