//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_ECS_SYSTEM_H_
#define INCLUDE_ECS_SYSTEM_H_

class SystemManager;
class EntityManager;

class ISystem {
  friend class SystemManager;
  bool is_enabled_ = true;
  int loading_order_;
  EntityManager *const entity_manager_;
  SystemManager *const system_manager_;

 protected:
  virtual void OnPreUpdate() {}
  virtual void OnUpdate() {}
  virtual void OnPostUpdate() {}

 public:
  ISystem(EntityManager *entity_manager, SystemManager *system_manager, int loading_order)
      : entity_manager_(entity_manager), system_manager_(system_manager), loading_order_(loading_order) {}
  virtual ~ISystem() = default;

  EntityManager *GetEntityManagerPtr() const {
    return entity_manager_;
  }
  EntityManager &GetEntityManager() const {
    return *GetEntityManagerPtr();
  }
  SystemManager *GetSystemManagerPtr() const {
    return system_manager_;
  }
  SystemManager &GetSystemManager() const {
    return *GetSystemManagerPtr();
  }
};

#endif  // INCLUDE_ECS_SYSTEM_H_
