#ifndef player_hpp
#define player_hpp

#include "Character.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "SharedContext.hpp"

class Player : public Object {
 public:
  Player(SharedContext* context);
  ~Player();

 private:
  Input* input;
  SharedContext* context;
  Character* character;
};

#endif