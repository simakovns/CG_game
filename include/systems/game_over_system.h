//
// Created by simakov on 18.07.2020.
//

#ifndef INCLUDE_SYSTEMS_GAME_OVER_SYSTEM_H_
#define INCLUDE_SYSTEMS_GAME_OVER_SYSTEM_H_

#include <controls.h>
#include <scenes/context.h>
#include <systems/data_transmitter.h>

#include "ecs/system.h"

class GameOverSystem : public ISystem {
  const Controls& controls_;
  Context* ctx_;
  DataTransmitter* datatransmitter_;

 protected:
  void GameOver();
  void CheckAllConditions();
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                 int loading_order, Context* ctx);
  GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                 int loading_order, Context* ctx, DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_GAME_OVER_SYSTEM_H_
