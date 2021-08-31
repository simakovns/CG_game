//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_SYSTEMS_SAVE_GAME_SYSTEM_H_
#define INCLUDE_SYSTEMS_SAVE_GAME_SYSTEM_H_

#include "ecs/system.h"

class SaveGameSystem : public ISystem {
 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  SaveGameSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order);
};

#endif  // INCLUDE_SYSTEMS_SAVE_GAME_SYSTEM_H_
