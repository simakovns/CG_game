//
// Created by simakov on 19.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <ecs/entity_manager.h>
#include <systems/save_game_system.h>

#include <cassert>
#include <fstream>   //NOLINT
#include <iostream>  //NOLINT
#include <string>

void SaveGameSystem::OnUpdate() {
  std::string name_of_save_file = "resources/savegame/savegame.dat";
  std::ofstream save_file(name_of_save_file, std::ios_base::trunc);
  assert(save_file.is_open());
  for (auto& e : GetEntityManager()) {
    if (e.Contains<PlayerComponent>()) {
      auto wallet = e.Get<PlayerComponent>()->wallet_;
      auto turn = e.Get<PlayerComponent>()->turn_;
      auto turns_left = e.Get<PlayerComponent>()->turns_left_;
      save_file << "//turns" << std::endl
                << turn << std::endl
                << "//wallet" << std::endl
                << wallet << std::endl
                << "//turns_left_" << std::endl
                << turns_left << std::endl;
    }
  }
}
void SaveGameSystem::OnPreUpdate() {
  terminal_clear();
}
void SaveGameSystem::OnPostUpdate() {
  terminal_refresh();
}
SaveGameSystem::SaveGameSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               int loading_order)
    : ISystem(entity_manager, system_manager, loading_order) {}
