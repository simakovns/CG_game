//
// Created by simakov on 18.07.2020.
//

#ifndef INCLUDE_SYSTEMS_PLAYER_MOVEMENT_SYSTEM_H_
#define INCLUDE_SYSTEMS_PLAYER_MOVEMENT_SYSTEM_H_

#include <controls.h>

#include "ecs/system.h"

class PlayerMovementSystem : public ISystem {
  const Controls& controls_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  PlayerMovementSystem(EntityManager* entity_manager, SystemManager* system_manager,
                       const Controls& controls, int loading_order);
};

#endif  // INCLUDE_SYSTEMS_PLAYER_MOVEMENT_SYSTEM_H_
