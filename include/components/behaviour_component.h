//
// Created by simakov on 19.07.2020.
//

#ifndef INCLUDE_COMPONENTS_BEHAVIOUR_COMPONENT_H_
#define INCLUDE_COMPONENTS_BEHAVIOUR_COMPONENT_H_

#include <ecs/component.h>
#include <mathutils/pair.h>

#include <string>

class BehaviourComponent : public IComponent {
 public:
  Pair spawn_point_;
  std::string beh_type_;
  int action_radius_;

  BehaviourComponent(Pair spawn_point, std::string beh_type, int action_radius)
      : spawn_point_(spawn_point), beh_type_(beh_type), action_radius_(action_radius) {}
};

#endif  // INCLUDE_COMPONENTS_BEHAVIOUR_COMPONENT_H_
