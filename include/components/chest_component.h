//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_CHEST_COMPONENT_H_
#define INCLUDE_COMPONENTS_CHEST_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class ChestComponent : public IComponent {
 public:
  int money_;
  bool IsEmpty = false;

  explicit ChestComponent(int money) : money_(money) {}
};

#endif  // INCLUDE_COMPONENTS_CHEST_COMPONENT_H_
