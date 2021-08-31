//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_COMPONENTS_POSITION_COMPONENT_H_
#define INCLUDE_COMPONENTS_POSITION_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

class PositionComponent : public IComponent {
 public:
  Pair pos_;

  explicit PositionComponent(Pair pos) : pos_(pos) {}
};

#endif  // INCLUDE_COMPONENTS_POSITION_COMPONENT_H_
