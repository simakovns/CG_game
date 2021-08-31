//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_COMPONENTS_LOOT_COMPONENT_H_
#define INCLUDE_COMPONENTS_LOOT_COMPONENT_H_

#include <ecs/component.h>

class LootComponent : public IComponent {
 public:
  int value_;

  explicit LootComponent(int value) : value_(value) {}
};

#endif  // INCLUDE_COMPONENTS_LOOT_COMPONENT_H_
