#ifndef cdrawable_hpp
#define cdrawable_hpp

#include <SFML/Graphics.hpp>

#include "Window.hpp"

enum class DrawLayer { Default, Background, Foreground, Entities };

class CDrawable {
 public:
  CDrawable();
  virtual ~CDrawable();
  virtual void Draw(Window& window) = 0;
  virtual bool ContinueToDraw() const = 0;
  void SetDrawLayer(DrawLayer drawLayer);
  DrawLayer GetDrawLayer() const;
  void SetSortOrder(int order);
  int GetSortOrder() const;

 private:
  int sortOrder;
  DrawLayer layer;
};

#endif