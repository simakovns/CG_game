//
// Created by simakov on 18.07.2020.
//

#ifndef INCLUDE_SYSTEMS_AI_BEHAVIOUR_SYSTEM_H_
#define INCLUDE_SYSTEMS_AI_BEHAVIOUR_SYSTEM_H_

#include <controls.h>
#include <ecs/entity.h>
#include <levels/char_file_reader.h>
#include <mathutils/pair.h>
#include <systems/data_transmitter.h>

#include <vector>

#include "ecs/system.h"

class AIBehaviourSystem : public ISystem {
  DataTransmitter* datatransmitter_;

  CharFileReader level_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

  bool CheckPosition(const Pair& position);

  void Follow(const Pair& player_pos, Entity* entity);
  void Wander(const Pair& spawn_point, const int& action_rad, Entity* entity);
  void MoveTo(const Pair& destination, Entity* entity);

  int CalculateDistance(const Pair& a, const Pair& b);

 public:
  AIBehaviourSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order,
                    DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_AI_BEHAVIOUR_SYSTEM_H_
