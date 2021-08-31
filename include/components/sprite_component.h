//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_SPRITE_COMPONENT_H_
#define INCLUDE_COMPONENTS_SPRITE_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class SpriteComponent : public IComponent {
 public:
  int sprite_;
  explicit SpriteComponent(int sprite) : sprite_(sprite) {}
};

#endif  // INCLUDE_COMPONENTS_SPRITE_COMPONENT_H_
