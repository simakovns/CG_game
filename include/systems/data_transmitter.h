//
// Created by simakov on 10.08.2020.
//
#ifndef INCLUDE_SYSTEMS_DATA_TRANSMITTER_H_
#define INCLUDE_SYSTEMS_DATA_TRANSMITTER_H_

#include <mathutils/pair.h>

#include <iostream>  // NOLINT
#include <map>
#include <string>
#include <vector>

class DataTransmitter {
 public:
  int turn_ = 0;
  int turns_left_ = 0;
  int wallet_ = 0;
  int key_count_ = 0;
  int potion_count_ = 0;
  int current_health_ = 0;
  int maximum_health_ = 0;
  int damage_ = 0;
  int strength_ = 0;
  int agility_ = 0;
  int armor_ = 0;
  int sprite_of_character_ = 0;
  int pic_of_character_ = 0;
  std::string destination_ = "";
  std::string prev_level = "";
  std::string next_level = "";
  std::string current_level = "";
  std::vector<std::string> level_array;
  int num_of_level_ = 0;
  bool IsGraphicsOn = false;
  bool OnExit = false;
  std::string character_ = "warrior";
  Pair pos_;
  int menu_cursor = 1;
  std::string file_name;
  std::map<size_t, size_t> CollidableEntitites;

  void FillLevelArray(const std::string& str) {
    if (level_array.empty()) {
      std::vector<std::string> temp(1, str);
      level_array = temp;
    } else {
      level_array.push_back(str);
    }
  }

  void SetCurrentLevel(const int& num_of_level) {
    if (num_of_level == 1) {
      prev_level = "";
      current_level = level_array[0];
      next_level = level_array[1];
    } else if (num_of_level == level_array.size()) {
      prev_level = level_array[level_array.size() - 2];
      current_level = level_array[level_array.size() - 1];
      next_level = "game_over";
    } else {
      prev_level = level_array[num_of_level - 2];
      current_level = level_array[num_of_level - 1];
      next_level = level_array[num_of_level];
    }
    num_of_level_ = num_of_level;
  }

  void Refresh() {
    turn_ = 0;
    wallet_ = 0;
    key_count_ = 0;
    potion_count_ = 0;
  }

  std::string GetCharacterName() {
    return ("resources/characters/" + character_ + ".dat");
  }

  DataTransmitter() = default;
};

#endif  // INCLUDE_SYSTEMS_DATA_TRANSMITTER_H_
