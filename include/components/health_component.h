//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_
#define INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class HealthComponent : public IComponent {
 public:
  int current_health_;
  int maximum_health_;
  HealthComponent(int max_health, int current_health) : maximum_health_(max_health), current_health_(current_health) {}
};

#endif  // INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_
