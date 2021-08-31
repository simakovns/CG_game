//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_EFFECTS_COMPONENT_H_
#define INCLUDE_COMPONENTS_EFFECTS_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class EffectsComponent : public IComponent {
 public:
  int stun_duration_ = 0;
  bool IsStunned_ = false;
  int poison_duration_ = 0;
  bool IsPoisoned = false;

  EffectsComponent() = default;
};

#endif  // INCLUDE_COMPONENTS_EFFECTS_COMPONENT_H_
