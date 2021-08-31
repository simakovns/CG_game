//
// Created by simakov on 18.07.2020.
//
#include <components/all_components.h>
#include <controls.h>
#include <ecs/entity_manager.h>
#include <systems/player_movement_system.h>

void PlayerMovementSystem::OnUpdate() {
  auto player_entity = GetEntityManager().Get(0);

  auto collision_syst = player_entity->Get<CollisionComponent>();
  collision_syst->new_position = player_entity->Get<PositionComponent>()->pos_ + controls_.Get_move_direction();
  if (controls_.Get_is_pressed_h() && player_entity->Get<PlayerComponent>()->potion_count_ != 0) {
    player_entity->Get<PlayerComponent>()->potion_count_ -= 1;
    player_entity->Get<HealthComponent>()->current_health_ += 20;
    if (player_entity->Get<HealthComponent>()->current_health_ >
        player_entity->Get<HealthComponent>()->maximum_health_) {
      player_entity->Get<HealthComponent>()->current_health_ = player_entity->Get<HealthComponent>()->maximum_health_;
    }
    player_entity->Get<PlayerComponent>()->turn_ += 1;
    player_entity->Get<PlayerComponent>()->turns_left_ -= 1;
  }
  if (controls_.Get_is_pressed_u()) {
    player_entity->Get<SkillComponent>()->IsActivated_ = true;
  }
}
void PlayerMovementSystem::OnPreUpdate() {}
void PlayerMovementSystem::OnPostUpdate() {}
PlayerMovementSystem::PlayerMovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                           const Controls& controls, int loading_order)
    : ISystem(entity_manager, system_manager, loading_order), controls_(controls) {}
