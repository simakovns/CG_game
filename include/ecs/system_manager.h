//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_ECS_SYSTEM_MANAGER_H_
#define INCLUDE_ECS_SYSTEM_MANAGER_H_

#include <ecs/entity_manager.h>
#include <ecs/system.h>

#include <map>
#include <memory>
#include <typeindex>

class SystemManager {
 private:
  std::map<std::type_index, std::unique_ptr<ISystem>> systems;
  EntityManager *const entity_manager;

 public:
  explicit SystemManager(EntityManager *entity_manager) : entity_manager(entity_manager) {}

  template<typename System, typename... Args>
  SystemManager *AddSystem(Args &&... args) {
    systems.emplace(typeid(System), std::make_unique<System>(entity_manager, this, std::forward<Args>(args)...));
    return this;
  }

  template<typename System>
  SystemManager *Delete() {
    systems.erase(typeid(System));
    return this;
  }

  SystemManager *DeleteAll() {
    systems.clear();
    return this;
  }

  template<typename System>
  void Disable() const {
    systems.at(typeid(System))->is_enabled_ = false;
  }

  template<typename System>
  void Enable() const {
    systems.at(typeid(System))->is_enabled_ = true;
  }

  void OnUpdate() {
    std::map<int, std::type_index> load_order;
    for (auto &p : systems) {
      load_order.emplace(p.second->loading_order_, p.first);
    }

    for (auto &p : systems) {
      if (p.second->is_enabled_) {
        p.second->OnPreUpdate();
      }
    }
    for (auto &p : load_order) {
      if ((systems.find(p.second))->second->is_enabled_) {
        (systems.find(p.second))->second->OnUpdate();
      }
    }
    for (auto &p : systems) {
      if (p.second->is_enabled_) {
        p.second->OnPostUpdate();
      }
    }
  }
};

#endif  // INCLUDE_ECS_SYSTEM_MANAGER_H_
