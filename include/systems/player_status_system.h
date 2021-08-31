//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_SYSTEMS_PLAYER_STATUS_SYSTEM_H_
#define INCLUDE_SYSTEMS_PLAYER_STATUS_SYSTEM_H_

#include <systems/data_transmitter.h>

#include <string>

#include "ecs/system.h"

class PlayerStatusSystem : public ISystem {
  DataTransmitter* datatransmitter_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
  void OnUpdateText();
  void OnUpdateSprites();
  void PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str,
                         const std::string& color = "white");
  void PrintStatusBarSprites(const int& x, const int& max_value, const int& current_value, const std::string& color);
  void PrintStatusBar(const int& x, const int& max_value, const int& current_value, const std::string& color);
  std::string GetColoredSymbol(const std::string& color, const char& symbol);

 public:
  PlayerStatusSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order);
  PlayerStatusSystem(EntityManager* const entity_manager, SystemManager* const system_manager, int loading_order,
                     DataTransmitter* datatransmitter);
};

#endif  // INCLUDE_SYSTEMS_PLAYER_STATUS_SYSTEM_H_
