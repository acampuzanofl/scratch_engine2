#ifndef cinstanceid_hpp
#define cinstanceid_hpp

#include "Component.hpp"

class CInstanceId : public Component {
 public:
  CInstanceId(Object* owner);
  ~CInstanceId();
  int GetInstanceId() const;

 private:
  static int count;
  int instanceId;
};

#endif