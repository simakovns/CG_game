//
// Created by simakov on 18.07.2020.
//

#ifndef INCLUDE_SYSTEMS_SKILL_SYSTEM_H_
#define INCLUDE_SYSTEMS_SKILL_SYSTEM_H_

#include <controls.h>
#include <ecs/entity.h>
#include <levels/char_file_reader.h>
#include <mathutils/pair.h>
#include <systems/data_transmitter.h>

#include <string>
#include <vector>

#include "ecs/system.h"

class SkillSystem : public ISystem {
  DataTransmitter* datatransmitter_;

  CharFileReader level_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

  bool CheckPosition(const Pair& position);

  void UseSkill(const std::string& name, Entity* player);

  void DrawIcons(const std::string& name, bool IsReady);

  void PrintStatus(const std::string &name, bool IsReady);

  void PrintParcedString(const int &x, const int &y, const int &dy, const std::string &str);

  int CalculateDistance(const Pair& a, const Pair& b);

 public:
  SkillSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order,
              DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_SKILL_SYSTEM_H_
