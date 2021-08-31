//
// Created by simakov on 18.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <controls.h>
#include <ecs/entity_manager.h>
#include <levels/char_file_reader.h>
#include <mathutils/rand.h>
#include <systems/ai_behaviour_system.h>
#include <systems/data_transmitter.h>

#include <cmath>
#include <iostream>  // NOLINT

bool AIBehaviourSystem::CheckPosition(const Pair &position) {
  if (level_.GetResourceMatrix()[position.second_][position.first_] == '#' ||
      level_.GetResourceMatrix()[position.second_][position.first_] == '@') {
    return false;
  } else {
    return true;
  }
}

int AIBehaviourSystem::CalculateDistance(const Pair &a, const Pair &b) {
  return (std::sqrt(std::pow(b.first_ - a.first_, 2) + std::pow(b.second_ - a.second_, 2)));
}

void AIBehaviourSystem::Follow(const Pair &player_pos, Entity *entity) {
  // TODO(simakovns): move only if player moves?
  RandomCreator rand;
  if (entity->Get<AIComponent>()->speed_ > rand.Get_random_int(0, 11)) {
    return;
  }
  auto enemy_pos_component = entity->Get<PositionComponent>();
  auto enemy_col_component = entity->Get<CollisionComponent>();
  Pair distance_between = player_pos - enemy_pos_component->pos_;
  enemy_col_component->new_position += enemy_pos_component->pos_;

  if (std::abs(distance_between.first_) >= std::abs(distance_between.second_)) {
    if (distance_between.first_ > 0) {
      if (CheckPosition(enemy_col_component->new_position + RIGHT)) {
        enemy_col_component->new_position += RIGHT;
      }
      return;
    } else if (distance_between.first_ < 0) {
      if (CheckPosition(enemy_col_component->new_position + LEFT)) {
        enemy_col_component->new_position += LEFT;
      }
      return;
    } else {
      return;
    }
  } else if (std::abs(distance_between.first_) < std::abs(distance_between.second_)) {
    if (distance_between.second_ > 0) {
      if (CheckPosition(enemy_col_component->new_position + DOWN)) {
        enemy_col_component->new_position += DOWN;
      }
      return;
    } else if (distance_between.second_ < 0) {
      if (CheckPosition(enemy_col_component->new_position + UP)) {
        enemy_col_component->new_position += UP;
      }
      return;
    } else {
      return;
    }
  }

  enemy_col_component->new_position = zero_pair;
}
void AIBehaviourSystem::Wander(const Pair &spawn_point, const int &action_rad, Entity *entity) {
  static int seed = 0;
  if (seed == 100000) {
    seed = 0;
  }
  RandomCreator rand;
  int wander_rad = action_rad / 2;
  Pair current_pos = entity->Get<PositionComponent>()->pos_;
  Pair *direction_array = new Pair[4];

  direction_array[0] = UP;
  direction_array[1] = DOWN;
  direction_array[2] = LEFT;
  direction_array[3] = RIGHT;

  Pair new_pos = direction_array[rand.Get_random_int(0, 4, seed)] + current_pos;

  if (CheckPosition(new_pos) && CalculateDistance(spawn_point, new_pos) < action_rad) {
    entity->Get<CollisionComponent>()->new_position = new_pos;
  } else {
    entity->Get<CollisionComponent>()->new_position = current_pos;
  }

  seed++;

  delete[] direction_array;
}
void AIBehaviourSystem::MoveTo(const Pair &destination, Entity *entity) {
  Follow(destination, entity);
}

void AIBehaviourSystem::OnUpdate() {
  level_.Read(datatransmitter_->file_name);

  const Pair player_pos = GetEntityManager().Get(0)->Get<PositionComponent>()->pos_;

  auto player = GetEntityManager().Get(0);
  bool TurnMade = false;
  static int turn = player->Get<PlayerComponent>()->turn_;

  if (turn != player->Get<PlayerComponent>()->turn_) {
    TurnMade = true;
    turn = player->Get<PlayerComponent>()->turn_;
  }

  for (auto &entity : GetEntityManager()) {
    if (entity.Contains<AIComponent>() && entity.Contains<BehaviourComponent>() && TurnMade) {
      const Pair spawn_pos = entity.Get<BehaviourComponent>()->spawn_point_;
      const int action_rad = entity.Get<BehaviourComponent>()->action_radius_;
      if (CalculateDistance(spawn_pos, player_pos) <= action_rad) {
        Follow(player_pos, &entity);
      } else {
        if (entity.Get<AIComponent>()->type_ == "wanderer") {
          Wander(spawn_pos, action_rad, &entity);
        }
        if (entity.Get<AIComponent>()->type_ == "guardian") {
          MoveTo(spawn_pos, &entity);
        }
      }
    }
  }
}
void AIBehaviourSystem::OnPreUpdate() {}
void AIBehaviourSystem::OnPostUpdate() {}
AIBehaviourSystem::AIBehaviourSystem(EntityManager *entity_manager, SystemManager *system_manager, int loading_order,
                                     DataTransmitter *datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}
