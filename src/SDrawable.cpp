#include "SDrawable.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "CDrawable.hpp"
#include "Component.hpp"

void SDrawable::Add(std::vector<std::shared_ptr<Object>> &object) {
  for (auto o : object) {
    Add(o);
  }
  Sort();
}

void SDrawable::Add(std::shared_ptr<Object> object) {
  std::shared_ptr<CDrawable> draw = object->GetDrawable();
  if (draw) {
    drawables.emplace_back(object);
  }
}

void SDrawable::Sort() {
  std::sort(drawables.begin(), drawables.end(),
            [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool {
              return a->GetDrawable()->GetSortOrder() <
                     b->GetDrawable()->GetSortOrder();
            });
}

void SDrawable::Draw(Window &window) {
  for (auto &d : drawables) {
    d->Draw(window);
  }
}

void SDrawable::ProcessRemovals() {
  drawables.erase(std::remove_if(drawables.begin(), drawables.end(),
                                 [](std::shared_ptr<Object> &o) {
                                   return o->IsQueuedForRemoval();
                                 }),
                  drawables.end());
}
