//
// Created by simakov on 18.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <controls.h>
#include <ecs/entity_manager.h>
#include <systems/game_over_system.h>

#include <iostream>  //NOLINT

void GameOverSystem::GameOver() {
  ctx_->scene_ = "game_over";
}

void GameOverSystem::CheckAllConditions() {
  for (auto& entity_1 : GetEntityManager()) {
    if (entity_1.Contains<TransferComponent>()) {
      if (entity_1.Get<TransferComponent>()->IsOnDoor_ &&
          (entity_1.Get<TransferComponent>()->destination_ == "game_over")) {
        GameOver();
      } else {
        ctx_->scene_ = entity_1.Get<TransferComponent>()->destination_;
      }
      if (entity_1.Get<PlayerComponent>()->turns_left_ == 0) {
        GameOver();
      }
      if (entity_1.Get<HealthComponent>()->current_health_ <= 0) {
        GameOver();
      }
    }
  }
}

void GameOverSystem::OnUpdate() {
  CheckAllConditions();
}
void GameOverSystem::OnPreUpdate() {
  terminal_clear();
}
void GameOverSystem::OnPostUpdate() {
  terminal_refresh();
}
GameOverSystem::GameOverSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               const Controls& controls, int loading_order, Context* ctx)
    : ISystem(entity_manager, system_manager, loading_order), controls_(controls), ctx_(ctx) {}

GameOverSystem::GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                               int loading_order, Context* ctx, DataTransmitter* datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order),
      controls_(controls),
      ctx_(ctx),
      datatransmitter_(datatransmitter) {}
