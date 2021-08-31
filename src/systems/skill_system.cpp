//
// Created by simakov on 18.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <controls.h>
#include <ecs/entity_manager.h>
#include <levels/char_file_reader.h>
#include <mathutils/rand.h>
#include <systems/data_transmitter.h>
#include <systems/skill_system.h>

#include <cmath>
#include <iostream>  // NOLINT
#include <string>

bool SkillSystem::CheckPosition(const Pair &position) {
  if (level_.GetResourceMatrix()[position.second_][position.first_] == '#') {
    return false;
  } else {
    return true;
  }
}

int SkillSystem::CalculateDistance(const Pair &a, const Pair &b) {
  return (std::sqrt(std::pow(b.first_ - a.first_, 2) + std::pow(b.second_ - a.second_, 2)));
}

void SkillSystem::PrintParcedString(const int &x, const int &y, const int &dy, const std::string &str) {
  int dx[4] = {-12, -4, 4, 12};

  if (dy > 0) {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 6);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
    }
  } else {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 3);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
    }
  }
  terminal_layer(2);
}

void SkillSystem::UseSkill(const std::string &name, Entity *player) {
  if (name == "slaughter") {
    player->Get<SkillComponent>()->current_cooldown = player->Get<SkillComponent>()->cooldown_;
    player->Get<SkillComponent>()->current_duration_ = player->Get<SkillComponent>()->duration_;
  }

  if (name == "bash") {
    player->Get<SkillComponent>()->current_cooldown = player->Get<SkillComponent>()->cooldown_;
    for (auto &entity_id : datatransmitter_->CollidableEntitites) {
      if (entity_id.first != 0) {
        auto entity = GetEntityManager().Get(entity_id.second);
        int dist = CalculateDistance(entity->Get<PositionComponent>()->pos_, player->Get<PositionComponent>()->pos_);
        if (dist < 10) {
          entity->Get<EffectsComponent>()->IsStunned_ = true;
          entity->Get<EffectsComponent>()->stun_duration_ = 10;
        }
      }
    }
  }

  if (name == "poison") {
    player->Get<SkillComponent>()->current_cooldown = player->Get<SkillComponent>()->cooldown_;
    player->Get<SkillComponent>()->current_duration_ = player->Get<SkillComponent>()->duration_;
  }
}

void SkillSystem::PrintStatus(const std::string &name, bool IsReady) {
  int box_x_size = (terminal_state(TK_WIDTH) - 30);

  auto player = GetEntityManager().Get(0);

  std::string name_;
  if (name == "bash") {
    name_ = "Устрашение: ";
  } else if (name == "slaughter") {
    name_ = "Резня: ";
  } else if (name == "poison") {
    name_ = "Отрава: ";
  }

  terminal_layer(2);

  if (IsReady) {
    terminal_printf(box_x_size + 3, 12, name_.c_str());
    terminal_print(box_x_size + name_.size() - 3, 12, "[color=green] готов [/color]");
  } else {
    terminal_printf(box_x_size + 3, 12, name_.c_str());
    terminal_print(box_x_size + name_.size() - 3, 12, "[color=red] не готов [/color]");
    std::string cd = "Откат: " + std::to_string(player->Get<SkillComponent>()->current_cooldown);
    std::string dur = "Длительность: " + std::to_string(player->Get<SkillComponent>()->current_duration_);
    terminal_printf(box_x_size + 3, 13, cd.c_str());
    terminal_printf(box_x_size + 3, 14, dur.c_str());
  }

  terminal_layer(3);
}

void SkillSystem::DrawIcons(const std::string &name, bool IsReady) {
  int box_x_size = static_cast<int>(std::round((terminal_state(TK_WIDTH) - 12)));
  int box_y_size = static_cast<int>(std::round(terminal_state(TK_HEIGHT)));

  auto player = GetEntityManager().Get(0);

  int sprite;
  if (name == "bash") {
    sprite = 0xE302;
  } else if (name == "slaughter") {
    sprite = 0xE301;
  } else if (name == "poison") {
    sprite = 0xE303;
  }

  terminal_layer(2);
  if (IsReady) {
    terminal_put_ext(box_x_size + 3, 9, -32, 0, 0xE304);
  } else {
    std::string cd = "CD: " + std::to_string(player->Get<SkillComponent>()->current_cooldown);
    std::string dur = "DUR: " + std::to_string(player->Get<SkillComponent>()->current_duration_);
    PrintParcedString(box_x_size + 1, 11, -8, cd);
    PrintParcedString(box_x_size + 1, 11, 8, dur);
    terminal_put_ext(box_x_size + 3, 9, -32, 0, 0xE305);
  }

  terminal_layer(3);
  terminal_put_ext(box_x_size + 3, 9, -30, 2, sprite);
}

void SkillSystem::OnUpdate() {
  level_.Read(datatransmitter_->file_name);

  bool TurnMade = false;
  auto player = GetEntityManager().Get(0);
  static int turn = player->Get<PlayerComponent>()->turn_;

  bool IsReady;

  if (player->Get<SkillComponent>()->current_cooldown == 0 && player->Get<SkillComponent>()->current_duration_ == 0) {
    IsReady = true;
  }

  if (turn != player->Get<PlayerComponent>()->turn_) {
    TurnMade = true;
    turn = player->Get<PlayerComponent>()->turn_;
  }

  if ((player->Get<SkillComponent>()->IsActivated_) && (player->Get<SkillComponent>()->current_cooldown == 0)) {
    UseSkill(player->Get<SkillComponent>()->skill_, player);
    IsReady = false;
  }

  if (datatransmitter_->IsGraphicsOn) {
    DrawIcons(player->Get<SkillComponent>()->skill_, IsReady);
  } else {
    PrintStatus(player->Get<SkillComponent>()->skill_, IsReady);
  }

  if (TurnMade) {
    if (player->Get<SkillComponent>()->current_duration_ > 0) {
      player->Get<SkillComponent>()->current_duration_ -= 1;
    } else {
      if (player->Get<SkillComponent>()->current_cooldown > 0) {
        player->Get<SkillComponent>()->current_cooldown -= 1;
      }
    }
  }

  player->Get<SkillComponent>()->IsActivated_ = false;
}
void SkillSystem::OnPreUpdate() {}
void SkillSystem::OnPostUpdate() {
  terminal_refresh();
}
SkillSystem::SkillSystem(EntityManager *entity_manager, SystemManager *system_manager, int loading_order,
                         DataTransmitter *datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}
