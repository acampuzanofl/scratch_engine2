#ifndef cdrawable_hpp
#define cdrawable_hpp

#include <SFML/Graphics.hpp>

#include "Window.hpp"

class CDrawable {
 public:
  CDrawable();
  virtual ~CDrawable();
  virtual void Draw(Window& window) = 0;
  void SetSortOrder(int order);
  int GetSortOrder() const;

 private:
  int sortOrder;
};

#endif