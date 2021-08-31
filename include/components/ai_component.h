//
// Created by simakov on 25.08.2020.
//

#ifndef INCLUDE_COMPONENTS_AI_COMPONENT_H_
#define INCLUDE_COMPONENTS_AI_COMPONENT_H_

#include <ecs/component.h>

#include <string>

class AIComponent : public IComponent {
 public:
  int money_;
  int speed_;
  int damage_;
  std::string type_;
  AIComponent(int money, int speed, std::string type, int damage)
      : money_(money), speed_(speed), type_(type), damage_(damage) {}
};

#endif  // INCLUDE_COMPONENTS_AI_COMPONENT_H_
