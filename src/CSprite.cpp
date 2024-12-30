#include "CSprite.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "Animation.hpp"
#include "CAnimation.hpp"
#include "Component.hpp"
#include "Debug.hpp"
#include "Object.hpp"
#include "SpriteMap.hpp"

CSprite::CSprite(Object *owner) : Component(owner), currentTextureId(-1) {}

void CSprite::Load(int textureid) {
  if (textureid >= 0 && textureid != currentTextureId) {
    currentTextureId = textureid;
    std::shared_ptr<sf::Texture> texture =
        owner->context->textureAllocator->Get(textureid);
    sprite->setTexture(*texture);
  }
}

void CSprite::Load(int textureid, int spritemapid) {
  if (textureid >= 0 && textureid != currentTextureId) {
    currentTextureId = textureid;
    std::shared_ptr<sf::Texture> texture =
        owner->context->textureAllocator->Get(textureid);
    sprite->setTexture(*texture);
  }
  if (spritemapid >= 0 && spritemapid != currentSpriteMapid) {
    currentSpriteMapid = spritemapid;
  }
}

void CSprite::Load(const std::string &textureFilePath) {
  if (owner->context->textureAllocator) {
    int textureID = owner->context->textureAllocator->Add(textureFilePath);
    if (textureID >= 0 && textureID != currentTextureId) {
      currentTextureId = textureID;
      std::shared_ptr<sf::Texture> texture =
          owner->context->textureAllocator->Get(textureID);
      sprite->setTexture(*texture);
    }
  }
}

void CSprite::Load(const std::string &textureFilePath,
                   const std::string &spriteMapFilePath) {
  if (owner->context->textureAllocator) {
    int textureID = owner->context->textureAllocator->Add(textureFilePath);
    if (textureID >= 0 && textureID != currentTextureId) {
      currentTextureId = textureID;
      std::shared_ptr<sf::Texture> texture =
          owner->context->textureAllocator->Get(textureID);
      sprite->setTexture(*texture);
    }
  } else {
    std::cout << "\033[91mtexture allocator not set\n\033[0m";
  }
  if (owner->context->spriteMapAllocator) {
    int spritemapid =
        owner->context->spriteMapAllocator->Add(spriteMapFilePath);
    if (spritemapid >= 0 && spritemapid != currentSpriteMapid) {
      currentSpriteMapid = spritemapid;
    }
  } else {
    std::cout << "\033[91mspriteMap allocator not set\n\033[0m";
  }
}

void CSprite::LateUpdate(float /*deltaTime*/) {
  sf::Vector2f pos = owner->transform->GetPosition();
  std::shared_ptr<CAnimation> currentAnimation =
      owner->GetComponent<CAnimation>();
  const SpriteMapData *currentFrame =
      currentAnimation->GetCurrentAnimation()->GetCurrentFrame();
  pos.x += currentFrame->sourceSizex;
  pos.y += currentFrame->sourceSizey;

  sf::Vector2f origin(currentFrame->sourcewidth / 2.f,
                      currentFrame->sourceheight / 2.f);

  sprite->setOrigin(origin);
  sprite->setPosition(pos);

  // debug sprite bounding boxes
  // sf::FloatRect boundingRect = sprite.getGlobalBounds();
  // Debug::DrawRect(boundingRect, sf::Color::Green);
}

void CSprite::Draw(Window &window) { 
        if (sprite) {
  window.Draw(*sprite);
    } else {
        Debug::Error("CSprite::GetSprite() return empty sprite.");
        exit(EXIT_FAILURE); // Return a default-constructed sprite
    }
 }

void CSprite::SetTextureRect(int x, int y, int width, int height) {
  sprite->setTextureRect(sf::IntRect({x, y}, {width, height}));
}

void CSprite::SetTextureRect(const sf::IntRect &rect) {
  sprite->setTextureRect(rect);
}

std::shared_ptr<Animation> CSprite::CreateAnimationFromSpriteMap(
    const std::string &animationName, float animationSpeed, bool loop) {
  std::shared_ptr<SpriteMap> spriteMap =
      owner->context->spriteMapAllocator->Get(currentSpriteMapid);

  std::shared_ptr<Animation> animation = std::make_shared<Animation>();
  animation->AddFrameList(spriteMap->CreateSpriteMapData(
                              currentTextureId, animationName, animationSpeed),
                          loop);
  return animation;
}

sf::Sprite CSprite::GetSprite() const { 
      if (sprite) {
        return *sprite; // Return the stored sprite
    } else {
        Debug::Error("CSprite::GetSprite() return empty sprite.");
        exit(EXIT_FAILURE); // Return a default-constructed sprite
    }
}
bool CSprite::ContinueToDraw() const { return !owner->IsQueuedForRemoval(); }