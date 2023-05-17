#include "SDrawable.hpp"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "CDrawable.hpp"
#include "Component.hpp"
#include "Object.hpp"

void SDrawable::Add(std::vector<std::shared_ptr<Object>> &object) {
  for (auto o : object) {
    Add(o);
  }
}

void SDrawable::Add(std::shared_ptr<Object> object) {
  std::shared_ptr<CDrawable> objectsDrawable = object->GetDrawable();
  if (objectsDrawable) {
    DrawLayer layer = objectsDrawable->GetDrawLayer();
    auto itr = drawables.find(layer);
    /**
     * Check to see if the layer exists in the map
     * if it doesn't make a new pair and add it into the map
     */
    if (itr != drawables.end()) {
      drawables[layer].push_back(objectsDrawable);
    } else {
      /**
       * Here we create a new vector of cdrawables for the
       * new layer that we are going to add.
       */
      std::vector<std::shared_ptr<CDrawable>> objs;
      objs.push_back(objectsDrawable);
      drawables.insert(std::make_pair(layer, objs));
    }
  }
}

void SDrawable::Sort() {
  for (auto &layer : drawables) {
    if (!std::is_sorted(layer.second.begin(), layer.second.end(), LayerSort)) {
      std::sort(layer.second.begin(), layer.second.end(), LayerSort);
    }
  }
}

bool SDrawable::LayerSort(std::shared_ptr<CDrawable> a,
                          std::shared_ptr<CDrawable> b) {
  return a->GetSortOrder() < b->GetSortOrder();
}

void SDrawable::Draw(Window &window) {
  Sort();

  for (auto &&layer : drawables) {
    for (auto &d : layer.second) {
      d->Draw(window);
    }
  }
}

void SDrawable::ProcessRemovals() {
  for (auto &layer : drawables) {
    layer.second.erase(std::remove_if(layer.second.begin(), layer.second.end(),
                                      [](std::shared_ptr<CDrawable> &o) {
                                        return !o->ContinueToDraw();
                                      }),
                       layer.second.end());
  }
}
