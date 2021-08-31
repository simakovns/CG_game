//
// Created by simakov on 25.08.2020.
//

#ifndef INCLUDE_COMPONENTS_STATS_COMPONENT_H_
#define INCLUDE_COMPONENTS_STATS_COMPONENT_H_

#include <ecs/component.h>

#include <string>

class StatsComponent : public IComponent {
 public:
  int damage_;
  int strength_;
  int agility_;
  int armor_;
  std::string type_;
  StatsComponent(int damage, int strength, int agility, int armor)
      : damage_(damage), strength_(strength), agility_(agility), armor_(armor) {}
};

#endif  // INCLUDE_COMPONENTS_STATS_COMPONENT_H_
