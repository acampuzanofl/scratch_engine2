#ifndef RESOURCEALLOCATOR_HPP
#define RESOURCEALLOCATOR_HPP

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "Debug.hpp"

template <typename T>
class ResourceAllocator {
 public:
  int Add(const std::string& filePath) {
    auto it = resources.find(filePath);
    if (it != resources.end()) {
      return it->second.first;
    }

    std::shared_ptr<T> resource = std::make_shared<T>();
    if (!resource->loadFromFile(filePath)) {
      Debug::Error("load failed: %s\n", filePath);
      return -1;
    }

    resources.insert(
        std::make_pair(filePath, std::make_pair(currentId, resource)));

    /**
     * TODO:
     * currentId is not initialized to any value, as a result i cant make any assumpts on what the value will
     * be when it returns currentId++. Fix is to learn how to initialize values or set defualt values using template
     */

    return currentId++;
  }

  void Remove(int id) {
    for (auto& it : resources) {
      if (it.second.first == id) {
        resources.erase(it.first);
      }
    }
  }

  std::shared_ptr<T> Get(int id) {
    for (auto& it : resources) {
      if (it.second.first == id) {
        return it.second.second;
      }
    }
    return nullptr;
  }

  bool Has(int id) { return (Get(id) != nullptr); }

 private:
  int currentId;
  std::map<std::string, std::pair<int, std::shared_ptr<T>>> resources;
};

#endif