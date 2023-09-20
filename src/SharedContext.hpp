#ifndef sharedcontext_hpp
#define sharedcontext_hpp
#include <SFML/Graphics/Texture.hpp>

#include "Input.hpp"
#include "ResourceAllocator.hpp"
#include "SpriteMap.hpp"
#include "Window.hpp"
#include "WorkingDirectory.hpp"

class ObjectCollection;

struct SharedContext {
  Input* input;
  ObjectCollection* objects;
  WorkingDirectory* workingDir;
  ResourceAllocator<sf::Texture>* textureAllocator;
  ResourceAllocator<SpriteMap>* spriteMapAllocator;
  Window* window;
};
#endif