//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SYSTEMS_SCORE_SYSTEM_H_
#define INCLUDE_SYSTEMS_SCORE_SYSTEM_H_

#include <systems/data_transmitter.h>

#include <string>

#include "ecs/system.h"

class ScoreSystem : public ISystem {
  DataTransmitter* datatransmitter_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
  void PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str);
  void OnCreateSprites();
  void OnCreateText();

 public:
  ScoreSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order);
  ScoreSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order,
              DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_SCORE_SYSTEM_H_
