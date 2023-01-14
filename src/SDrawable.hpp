#ifndef sdrawable_hpp
#define sdrawable_hpp

#include <map>
#include <memory>
#include <vector>

#include "CDrawable.hpp"
#include "Object.hpp"
#include "Window.hpp"

// TODO
//  We currently do not support layers. It would be good if we could set a group
//  of sprites as a background layer for example and have them always drawn
//  before subsequent layers. We are drawing everything regardless of whether it
//  is onscreen to not. We should add Occlusion Culling. We have a limit of one
//  drawable per object. In future, we will want to add more. If we add a new
//  drawable component to an object the drawable system will not sort its
//  collection to accommodate the new object, consequently, it is likely that
//  the object will be drawn out of order.

class SDrawable {
 public:
  void Add(std::vector<std::shared_ptr<Object>>& object);
  void ProcessRemovals();
  void Draw(Window& window);

 private:
  void Add(std::shared_ptr<Object> object);
  void Sort();
  std::vector<std::shared_ptr<Object>> drawables;
};

#endif