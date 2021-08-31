//
// Created by simakov on 18.07.2020.
//

#ifndef INCLUDE_COMPONENTS_PLAYER_COMPONENT_H_
#define INCLUDE_COMPONENTS_PLAYER_COMPONENT_H_

#include <ecs/component.h>

class PlayerComponent : public IComponent {
 public:
  int wallet_ = 0;
  int turn_ = 0;
  int turns_left_ = 0;
  int key_count_ = 0;
  int potion_count_ = 0;

  PlayerComponent(int wallet, int turn, int turns_left) : wallet_(wallet), turn_(turn), turns_left_(turns_left) {}
  PlayerComponent(int wallet, int turn, int turns_left, int key_count, int potion_count)
      : wallet_(wallet), turn_(turn), turns_left_(turns_left), key_count_(key_count), potion_count_(potion_count) {}
};

#endif  // INCLUDE_COMPONENTS_PLAYER_COMPONENT_H_
