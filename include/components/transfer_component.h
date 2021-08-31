#ifndef INCLUDE_COMPONENTS_TRANSFER_COMPONENT_H_
#define INCLUDE_COMPONENTS_TRANSFER_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class TransferComponent : public IComponent {
 public:
  bool IsOnDoor_ = true;
  std::string destination_;

  TransferComponent(bool IsOnDoor, std::string destination) : IsOnDoor_(IsOnDoor), destination_(destination) {}
};

#endif  // INCLUDE_COMPONENTS_TRANSFER_COMPONENT_H_
