#ifndef INCLUDE_COMPONENTS_DOOR_COMPONENT_H_
#define INCLUDE_COMPONENTS_DOOR_COMPONENT_H_

#include <ecs/component.h>

#include <string>

class DoorComponent : public IComponent {
 public:
  std::string transfer_to_level_;
  explicit DoorComponent(std::string level_name) : transfer_to_level_(level_name) {}
};

#endif  // INCLUDE_COMPONENTS_DOOR_COMPONENT_H_
