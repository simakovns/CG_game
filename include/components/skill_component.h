//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_SKILL_COMPONENT_H_
#define INCLUDE_COMPONENTS_SKILL_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class SkillComponent : public IComponent {
 public:
  int cooldown_;
  int current_cooldown = 0;
  std::string skill_;
  bool IsActivated_ = false;
  int duration_ = 0;
  int current_duration_ = 0;

  SkillComponent(int cooldown, std::string skill) : cooldown_(cooldown), skill_(skill) {}

  SkillComponent(int cooldown, std::string skill, int duration)
      : cooldown_(cooldown), skill_(skill), duration_(duration) {}
};

#endif  // INCLUDE_COMPONENTS_SKILL_COMPONENT_H_
