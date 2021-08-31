//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_COLLISION_COMPONENT_H_
#define INCLUDE_COMPONENTS_COLLISION_COMPONENT_H_

#include <ecs/component.h>

#include <mathutils/pair.h>

class CollisionComponent : public IComponent {
 public:
  Pair new_position = {0, 0};

  CollisionComponent() = default;
};

#endif  // INCLUDE_COMPONENTS_COLLISION_COMPONENT_H_
