//
// Created by simakov on 21.07.2020.
//
#include <components/all_components.h>
#include <ecs/entity.h>
#include <ecs/entity_manager.h>
#include <mathutils/pair.h>
#include <mathutils/rand.h>
#include <systems/collision_system.h>
#include <systems/data_transmitter.h>

#include <iostream>  //NOLINT
#include <string>

bool CollisionSystem::HasPosition(const Entity* entity_) {
  return entity_->Contains<PositionComponent>();
}

bool CollisionSystem::HasCollision(const Entity* entity_) {
  return entity_->Contains<CollisionComponent>();
}

void CollisionSystem::PlayerMoneyCollision(Entity* entity_1, Entity* entity_2) {
  size_t id_of_entity = entity_2->GetId();
  entity_1->Get<PlayerComponent>()->wallet_ += entity_2->Get<LootComponent>()->value_;
  datatransmitter_->wallet_ = entity_1->Get<PlayerComponent>()->wallet_;
  GetEntityManager().DeleteEntity(id_of_entity);
  entity_1->Get<PositionComponent>()->pos_ = entity_1->Get<CollisionComponent>()->new_position;
  entity_1->Get<CollisionComponent>()->new_position = zero_pair;
  AddTurnToPlayer(entity_1);
  datatransmitter_->pos_ = entity_1->Get<PositionComponent>()->pos_;
}

void CollisionSystem::PlayerKeyCollision(Entity* entity_1, Entity* entity_2) {
  size_t id_of_entity = entity_2->GetId();
  entity_1->Get<PlayerComponent>()->key_count_ += 1;
  datatransmitter_->key_count_ = entity_1->Get<PlayerComponent>()->key_count_;
  GetEntityManager().DeleteEntity(id_of_entity);
  entity_1->Get<PositionComponent>()->pos_ = entity_1->Get<CollisionComponent>()->new_position;
  entity_1->Get<CollisionComponent>()->new_position = zero_pair;
  AddTurnToPlayer(entity_1);
  datatransmitter_->pos_ = entity_1->Get<PositionComponent>()->pos_;
}

void CollisionSystem::Poison(Entity* entity_1, Entity* entity_2) {
  if (entity_1->Get<SkillComponent>()->skill_ == "poison" && entity_1->Get<SkillComponent>()->current_duration_ > 0) {
    entity_2->Get<EffectsComponent>()->IsPoisoned = true;
    entity_2->Get<EffectsComponent>()->poison_duration_ = 5;
  }
}

void CollisionSystem::GetPoisonDamage(Entity* entity_1, Entity* entity_2) {
  if (entity_1->Get<SkillComponent>()->skill_ == "poison") {
    if (entity_2->Get<EffectsComponent>()->IsPoisoned && entity_2->Get<EffectsComponent>()->poison_duration_ > 0) {
      entity_2->Get<EffectsComponent>()->poison_duration_ -= 1;
      entity_2->Get<HealthComponent>()->current_health_ -= 10;
      entity_1->Get<SkillComponent>()->duration_ -= 1;
    }
    if (entity_2->Get<EffectsComponent>()->poison_duration_ == 0) {
      entity_2->Get<EffectsComponent>()->IsPoisoned = false;
    }
  }
}

void CollisionSystem::Battle(Entity* entity_1, Entity* entity_2) {
  RandomCreator rand;

  GetPoisonDamage(entity_1, entity_2);

  if (entity_2->Get<EffectsComponent>()->stun_duration_ == 0) {
    entity_2->Get<EffectsComponent>()->IsStunned_ = false;
  }

  auto p_stat = entity_1->Get<StatsComponent>();

  int player_damage = p_stat->damage_;

  bool Evaded;

  double damage_absorbation = static_cast<double>(p_stat->armor_) / static_cast<double>(100);
  double crit_chance = static_cast<double>(p_stat->strength_) / static_cast<double>(100);
  double evasion_chance = static_cast<double>(p_stat->agility_) / static_cast<double>(100);

  if (entity_1->Get<SkillComponent>()->skill_ == "slaughter" &&
      entity_1->Get<SkillComponent>()->current_duration_ > 0) {
    damage_absorbation = 1.0;
    crit_chance *= 2;
  }

  double random_number = rand.Get_double_0_1();

  if (random_number < crit_chance) {
    player_damage *= 2;
  }
  Evaded = random_number < evasion_chance;

  int enemy_damage = entity_2->Get<AIComponent>()->damage_ -
                     (static_cast<double>(entity_2->Get<AIComponent>()->damage_) * damage_absorbation);

  if (entity_2->Get<EffectsComponent>()->IsStunned_ && entity_2->Get<EffectsComponent>()->stun_duration_ > 0) {
    entity_2->Get<EffectsComponent>()->stun_duration_ -= 1;
    entity_2->Get<CollisionComponent>()->new_position = zero_pair;
    enemy_damage = 0;
  }

  entity_2->Get<HealthComponent>()->current_health_ -= player_damage;
  if (!Evaded) {
    entity_1->Get<HealthComponent>()->current_health_ -= enemy_damage;
    datatransmitter_->current_health_ -= enemy_damage;
  }
}

void CollisionSystem::PlayerEnemyCollision(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() != 0) {
    auto p = entity_2;
    entity_2 = entity_1;
    entity_1 = p;
  }
  size_t id_of_entity = entity_2->GetId();

  Battle(entity_1, entity_2);

  if (entity_2->Get<HealthComponent>()->current_health_ <= 0) {
    GetEntityManager().DeleteEntity(id_of_entity);
    datatransmitter_->CollidableEntitites.erase(id_of_entity);
    if (entity_1->Get<CollisionComponent>()->new_position != zero_pair) {
      entity_1->Get<PositionComponent>()->pos_ = entity_1->Get<CollisionComponent>()->new_position;
      entity_1->Get<CollisionComponent>()->new_position = zero_pair;
    }
  } else {
    Poison(entity_1, entity_2);
    auto new_pos_1 = entity_1->Get<CollisionComponent>();
    new_pos_1->new_position = entity_1->Get<PositionComponent>()->pos_;
    entity_2->Get<CollisionComponent>()->new_position = entity_2->Get<PositionComponent>()->pos_;
    entity_2->Get<CollisionComponent>()->new_position = zero_pair;
  }

  AddTurnToPlayer(entity_1);
  datatransmitter_->pos_ = entity_1->Get<PositionComponent>()->pos_;
}

void CollisionSystem::PlayerPotionCollision(Entity* entity_1, Entity* entity_2) {
  size_t id_of_entity = entity_2->GetId();
  entity_1->Get<PlayerComponent>()->potion_count_ += 1;
  datatransmitter_->potion_count_ = entity_1->Get<PlayerComponent>()->potion_count_;
  GetEntityManager().DeleteEntity(id_of_entity);
  entity_1->Get<PositionComponent>()->pos_ = entity_1->Get<CollisionComponent>()->new_position;
  entity_1->Get<CollisionComponent>()->new_position = zero_pair;
  AddTurnToPlayer(entity_1);
  datatransmitter_->pos_ = entity_1->Get<PositionComponent>()->pos_;
}
void CollisionSystem::PlayerWallCollision(Entity* entity_1, Entity* entity_2) {
  auto new_pos_1 = entity_1->Get<CollisionComponent>();
  new_pos_1->new_position = zero_pair;
}

void CollisionSystem::EnemyEntityCollision(Entity* entity_1, Entity* entity_2) {
  auto new_pos_1 = entity_1->Get<CollisionComponent>();
  new_pos_1->new_position = zero_pair;
}

void CollisionSystem::PlayerChestCollision(Entity* entity_1, Entity* entity_2) {
  if (entity_1->Get<PlayerComponent>()->key_count_ == 0) {
    auto new_pos_1 = entity_1->Get<CollisionComponent>();
    new_pos_1->new_position = zero_pair;
    return;
  }
  if (!entity_2->Get<ChestComponent>()->IsEmpty) {
    entity_1->Get<PlayerComponent>()->key_count_ -= 1;
    entity_1->Get<PlayerComponent>()->wallet_ += entity_2->Get<ChestComponent>()->money_;
    entity_2->Get<ChestComponent>()->IsEmpty = true;
    entity_2->Get<SpriteComponent>()->sprite_ = 0xE013;
  }
  auto new_pos_1 = entity_1->Get<CollisionComponent>();
  new_pos_1->new_position = zero_pair;
}

void CollisionSystem::PlayerDoorCollision(Entity* entity_1, Entity* entity_2) {
  auto transfer = entity_1->Get<TransferComponent>();
  transfer->IsOnDoor_ = true;
  datatransmitter_->destination_ = transfer->destination_ + "_" + entity_2->Get<DoorComponent>()->transfer_to_level_;
  std::cout << datatransmitter_->destination_ << std::endl;
  transfer->destination_ = entity_2->Get<DoorComponent>()->transfer_to_level_;
  if (datatransmitter_->next_level == entity_2->Get<DoorComponent>()->transfer_to_level_) {
    int num = datatransmitter_->num_of_level_;
    datatransmitter_->SetCurrentLevel(++num);
  }
  if (datatransmitter_->prev_level == entity_2->Get<DoorComponent>()->transfer_to_level_) {
    int num = datatransmitter_->num_of_level_;
    datatransmitter_->SetCurrentLevel(--num);
  }
}

void CollisionSystem::AddTurnToPlayer(const Entity* entity) {
  if (entity->Contains<PlayerComponent>()) {
    entity->Get<PlayerComponent>()->turn_ += 1;
    entity->Get<PlayerComponent>()->turns_left_ -= 1;
    datatransmitter_->turns_left_ -= 1;
    datatransmitter_->turn_ += 1;
  }
}

void CollisionSystem::CallCollisionFunction(const std::string& name, Entity* entity_1, Entity* entity_2) {
  auto iter = CollisionMap.find(name);
  if (iter == CollisionMap.end()) {
    return;
  }
  (this->*CollisionMap[name])(entity_1, entity_2);
}

void CollisionSystem::FillCollisionMap() {
  CollisionMap.emplace("playermoney", &CollisionSystem::PlayerMoneyCollision);
  CollisionMap.emplace("playerwall", &CollisionSystem::PlayerWallCollision);
  CollisionMap.emplace("playerdoor", &CollisionSystem::PlayerDoorCollision);
  CollisionMap.emplace("playerchest", &CollisionSystem::PlayerChestCollision);
  CollisionMap.emplace("playerkey", &CollisionSystem::PlayerKeyCollision);
  CollisionMap.emplace("playerpotion", &CollisionSystem::PlayerPotionCollision);
  CollisionMap.emplace("playerenemy", &CollisionSystem::PlayerEnemyCollision);
  CollisionMap.emplace("enemyplayer", &CollisionSystem::PlayerEnemyCollision);
  CollisionMap.emplace("enemymoney", &CollisionSystem::EnemyEntityCollision);
  CollisionMap.emplace("enemywall", &CollisionSystem::EnemyEntityCollision);
  CollisionMap.emplace("enemydoor", &CollisionSystem::EnemyEntityCollision);
  CollisionMap.emplace("enemychest", &CollisionSystem::EnemyEntityCollision);
  CollisionMap.emplace("enemyenemy", &CollisionSystem::EnemyEntityCollision);
}

void CollisionSystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }
  FillCollisionMap();
  CallCollisionFunction(entity_1->GetName() + entity_2->GetName(), entity_1, entity_2);
}

void CollisionSystem::Move(Entity* entity) {
  if (entity->Contains<EffectsComponent>()) {
    if (entity->Get<EffectsComponent>()->IsStunned_ && entity->Get<EffectsComponent>()->stun_duration_ > 0) {
      entity->Get<EffectsComponent>()->stun_duration_ -= 1;
      entity->Get<CollisionComponent>()->new_position = entity->Get<PositionComponent>()->pos_;
    }

    if (entity->Get<EffectsComponent>()->stun_duration_ == 0) {
      entity->Get<EffectsComponent>()->IsStunned_ = false;
    }
  }
  if (entity->Get<CollisionComponent>()->new_position != zero_pair) {
    auto old_position = entity->Get<PositionComponent>()->pos_;
    entity->Get<PositionComponent>()->pos_ = entity->Get<CollisionComponent>()->new_position;
    entity->Get<CollisionComponent>()->new_position = zero_pair;
    if (entity->Contains<PlayerComponent>()) {
      auto new_pos = entity->Get<PositionComponent>()->pos_;
      if (old_position != new_pos) {
        AddTurnToPlayer(entity);
      }
      datatransmitter_->pos_ = entity->Get<PositionComponent>()->pos_;
    }
  }
}

void CollisionSystem::OnUpdate() {
  for (auto& entity_1_id : datatransmitter_->CollidableEntitites) {
    auto entity_1 = GetEntityManager().Get(entity_1_id.second);
    if (HasPosition(entity_1) && HasCollision(entity_1)) {
      auto position_1 = entity_1->Get<CollisionComponent>()->new_position;
      auto position_1_old = entity_1->Get<PositionComponent>()->pos_;
      if (entity_1->Contains<CollisionComponent>() && (position_1 != zero_pair)) {
        for (auto& entity_2 : GetEntityManager()) {
          if (HasPosition(&entity_2) && HasCollision(&entity_2)) {
            auto position_2 = entity_2.Get<PositionComponent>()->pos_;
            auto position_2_new = entity_2.Get<CollisionComponent>()->new_position;
            if (position_1 == position_2 || position_1_old == position_2_new) {
              Collide(entity_1, &entity_2);
            }
          }
        }
        if (datatransmitter_->CollidableEntitites.find(entity_1_id.first) !=
            datatransmitter_->CollidableEntitites.end()) {
          Move(entity_1);
        }
      }
    }
  }
}

void CollisionSystem::OnPreUpdate() {}
void CollisionSystem::OnPostUpdate() {}
CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                 int loading_order, DataTransmitter* datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}
