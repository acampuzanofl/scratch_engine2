#include "CSprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

#include "Animation.hpp"
#include "CAnimation.hpp"
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
  std::shared_ptr<CAnimation> currentAnimation =
      owner->GetComponent<CAnimation>();
  const SpriteFrameData *currentFrame =
      currentAnimation->GetCurrentAnimation()->GetCurrentFrame();
  // if (currentFrame->isRotated) {
  //   sprite.setRotation(-90.f);
  //   // pos.y += currentFrame->sourceSizeheight;
  //   pos.y += (currentFrame->frameheight);
  // } else {
  //   sprite.setRotation(0.f);
  // }
  pos.x += currentFrame->sourceSizex;
  pos.y += currentFrame->sourceSizey;
  sprite.setPosition(pos);
}

void CSprite::Draw(Window &window) {
  window.Draw(sprite);

  // debug sprite
  // sf::FloatRect boundingRect = sprite.getLocalBounds();
  // sf::RectangleShape rect(
  //     sf::Vector2f(boundingRect.width, boundingRect.height));

  // rect.setPosition(sprite.getPosition());
  // rect.setFillColor(sf::Color(0, 0, 0, 0));
  // rect.setOutlineColor(sf::Color::Red);
  // rect.setOutlineThickness(1.0f);
  // window.Draw(rect);
}

void CSprite::SetTextureRect(int x, int y, int width, int height) {
  sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void CSprite::SetTextureRect(const sf::IntRect &rect) {
  sprite.setTextureRect(rect);
}