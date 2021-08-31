//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_SYSTEMS_LOAD_GAME_SYSTEM_H_
#define INCLUDE_SYSTEMS_LOAD_GAME_SYSTEM_H_

#include "ecs/system.h"

class LoadGameSystem {
 public:
  int wallet_;
  int turn_;
  int turns_left_;
  void OnPreUpdate();
  void OnUpdate();
  void OnPostUpdate();
  LoadGameSystem() = default;
};

#endif  // INCLUDE_SYSTEMS_LOAD_GAME_SYSTEM_H_
