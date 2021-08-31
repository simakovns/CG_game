//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_ECS_ENGINE_H_
#define INCLUDE_ECS_ENGINE_H_

#include <ecs/entity_manager.h>
#include <ecs/system_manager.h>

#include <memory>

class Engine {
 private:
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;

 public:
  Engine()
      : entity_manager_(std::make_unique<EntityManager>()),
        system_manager_(std::make_unique<SystemManager>(entity_manager_.get())) {}

  EntityManager* GetEntityManager() const {
    return entity_manager_.get();
  }
  SystemManager* GetSystemManager() const {
    return system_manager_.get();
  }

  void OnUpdate() const {
    system_manager_->OnUpdate();
  }
};

#endif  // INCLUDE_ECS_ENGINE_H_
