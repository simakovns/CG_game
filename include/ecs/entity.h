//
// Created by simakov on 16.07.2020.
//

#ifndef INCLUDE_ECS_ENTITY_H_
#define INCLUDE_ECS_ENTITY_H_

#include <ecs/component.h>

#include <iostream>  //NOLINT
#include <map>
#include <memory>
#include <string>
#include <typeindex>

class Entity {
  friend class EntityManager;

 private:
  std::map<std::type_index, std::unique_ptr<IComponent>> components;
  size_t id = 0;
  std::string name_;

 public:
  explicit Entity(size_t id) : id(id) {}
  Entity(size_t id, std::string name) : id(id), name_(name) {}

  template<typename Component, typename... Args>
  Entity* Add(Args&&... args) {
    components[typeid(Component)] = std::make_unique<Component>(std::forward<Args>(args)...);
    return this;
  }

  size_t GetId() const {
    return id;
  }

  std::string GetName() const {
    return name_;
  }

  template<typename Component>
  Component* Get() const {
    auto c = components.at(typeid(Component)).get();
    return dynamic_cast<Component*>(c);
  }

  template<typename Component>
  bool Contains() const {
    return components.count(typeid(Component)) != 0;
  }

  template<typename Component>
  void Delete() {
    components.erase(typeid(Component));
  }
};
#endif  // INCLUDE_ECS_ENTITY_H_
