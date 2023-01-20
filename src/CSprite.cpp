#include "CSprite.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "Component.hpp"
#include "Object.hpp"
#include "SpriteMap.hpp"

CSprite::CSprite(Object *owner) : Component(owner), currentTextureId(-1) {}

void CSprite::SetAllocator(ResourceAllocator<sf::Texture> *allocator) {
  this->textureAllocator = allocator;
}

void CSprite::SetAllocator(ResourceAllocator<SpriteMap> *allocator) {
  this->spriteMapAllocator = allocator;
}

void CSprite::Load(int textureid) {
  if (textureid >= 0 && textureid != currentTextureId) {
    currentTextureId = textureid;
    std::shared_ptr<sf::Texture> texture = textureAllocator->Get(textureid);
    sprite.setTexture(*texture);
  }
}

void CSprite::Load(int textureid, int spritemapid) {
  if (textureid >= 0 && textureid != currentTextureId) {
    currentTextureId = textureid;
    std::shared_ptr<sf::Texture> texture = textureAllocator->Get(textureid);
    sprite.setTexture(*texture);
  }
  if (spritemapid >= 0 && spritemapid != currentSpriteMapid) {
    currentSpriteMapid = spritemapid;
  }
}

void CSprite::Load(const std::string &textureFilePath) {
  if (textureAllocator) {
    int textureID = textureAllocator->Add(textureFilePath);
    if (textureID >= 0 && textureID != currentTextureId) {
      currentTextureId = textureID;
      std::shared_ptr<sf::Texture> texture = textureAllocator->Get(textureID);
      sprite.setTexture(*texture);
    }
  }
}

void CSprite::Load(const std::string &textureFilePath,
                   const std::string &spriteMapFilePath) {
  if (textureAllocator) {
    int textureID = textureAllocator->Add(textureFilePath);
    if (textureID >= 0 && textureID != currentTextureId) {
      currentTextureId = textureID;
      std::shared_ptr<sf::Texture> texture = textureAllocator->Get(textureID);
      sprite.setTexture(*texture);
    }
  } else {
    std::cout << "\033[91mtexture allocator not set\n\033[0m";
  }
  if (spriteMapAllocator) {
    int spritemapid = spriteMapAllocator->Add(spriteMapFilePath);
    if (spritemapid >= 0 && spritemapid != currentSpriteMapid) {
      currentSpriteMapid = spritemapid;
    }
  } else {
    std::cout << "\033[91mspriteMap allocator not set\n\033[0m";
  }
}

void CSprite::LateUpdate(float deltaTime) {
  sf::Vector2f pos = owner->transform->GetPosition();
  std::shared_ptr<CAnimation> currentAnimation =
      owner->GetComponent<CAnimation>();
  const SpriteMapData *currentFrame =
      currentAnimation->GetCurrentAnimation()->GetCurrentFrame();
  pos.x += currentFrame->sourceSizex;
  pos.y += currentFrame->sourceSizey;
  sprite.setOrigin(
      currentFrame->sourcewidth / 2.f,
      currentFrame->sourceheight / 2.f);  // sourcewidth and sourcheigth
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

std::shared_ptr<Animation> CSprite::CreateAnimationFromSpriteMap(
    const std::string &animationName, float animationSpeed) {
  std::shared_ptr<SpriteMap> spriteMap =
      spriteMapAllocator->Get(currentSpriteMapid);

  std::shared_ptr<Animation> animation =
      std::make_shared<Animation>(FacingDirection::Right);
  animation->AddFrameList(spriteMap->CreateSpriteMapData(
      currentTextureId, animationName, animationSpeed));
  return animation;
}

sf::Sprite CSprite::GetSprite() const { return sprite; }