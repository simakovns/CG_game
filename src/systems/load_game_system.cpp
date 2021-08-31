//
// Created by simakov on 19.07.2020.
//
#include <BearLibTerminal.h>
#include <systems/load_game_system.h>

#include <cassert>
#include <fstream>  // NOLINT
#include <string>

void LoadGameSystem::OnUpdate() {
  std::string name_of_save_file = "resources/savegame/savegame.dat";
  std::ifstream save_file(name_of_save_file);
  assert(save_file.is_open());
  std::string line;
  save_file >> line >> turn_ >> line >> wallet_ >> line >> turns_left_;
}
void LoadGameSystem::OnPreUpdate() {
  terminal_clear();
}
void LoadGameSystem::OnPostUpdate() {
  terminal_refresh();
}
