//
// Created by simakov on 21.07.2020.
//
#ifndef INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_
#define INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_
#include <controls.h>
#include <ecs/entity.h>
#include <systems/data_transmitter.h>

#include <map>
#include <string>

#include "ecs/system.h"

class CollisionSystem : public ISystem {
  DataTransmitter* datatransmitter_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  typedef void (CollisionSystem::*CollisionFunc)(Entity*, Entity*);
  std::map<std::string, CollisionFunc> CollisionMap;

  bool HasPosition(const Entity* entity_);

  bool HasCollision(const Entity* entity_);

  void FillCollisionMap();
  void CallCollisionFunction(const std::string& name, Entity* entity_1, Entity* entity_2);
  void PlayerMoneyCollision(Entity* entity_1, Entity* entity_2);
  void PlayerWallCollision(Entity* entity_1, Entity* entity_2);
  void PlayerChestCollision(Entity* entity_1, Entity* entity_2);
  void PlayerDoorCollision(Entity* entity_1, Entity* entity_2);
  void PlayerKeyCollision(Entity* entity_1, Entity* entity_2);
  void PlayerEnemyCollision(Entity* entity_1, Entity* entity_2);
  void PlayerPotionCollision(Entity* entity_1, Entity* entity_2);
  void EnemyEntityCollision(Entity* entity_1, Entity* entity_2);

  void Poison(Entity* entity_1, Entity* entity_2);
  void Battle(Entity* entity_1, Entity* entity_2);
  void GetPoisonDamage(Entity* entity_1, Entity* entity_2);

  void AddTurnToPlayer(const Entity* entity);

  void Collide(Entity* entity_1, Entity* entity_2);

  void Move(Entity* entity);
  CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager, int loading_order,
                  DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_
