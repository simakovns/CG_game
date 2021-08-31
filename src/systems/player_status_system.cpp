//
// Created by simakov on 19.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <ecs/entity_manager.h>
#include <systems/player_status_system.h>

#include <string>

std::string PlayerStatusSystem::GetColoredSymbol(const std::string& color, const char& symbol) {
  std::string color_ = "[color=" + color + "]";
  std::string symbol_to_string(1, symbol);
  return (color_ + symbol_to_string + "[/color]");
}

void PlayerStatusSystem::PrintStatusBar(const int& x, const int& max_value, const int& current_value,
                                        const std::string& color) {
  terminal_layer(11);
  const int length_of_line = 10;
  const int length_of_array = length_of_line + 2;
  char line_array[length_of_array];  // NOLINT

  line_array[0] = '|';
  line_array[length_of_array - 1] = ')';

  for (int i = 1; i < length_of_array - 1; ++i) {
    line_array[i] = '-';
  }

  double percent = current_value * length_of_line / max_value;

  for (int i = 1; i <= static_cast<int>(percent); ++i) {
    if (i != length_of_array - 1) {
      line_array[i] = '|';
    }
  }
  line_array[length_of_array - 1] = ')';
  int j = 0;
  for (int i = 0; i < length_of_array; ++i) {
    terminal_print(x + 3 + length_of_array + i, 10, GetColoredSymbol(color, line_array[i]).c_str());
  }
  line_array[length_of_array - 1] = '(';

  for (int i = length_of_array - 1; i >= 0; --i) {
    terminal_print(x + 3 + j, 10, GetColoredSymbol(color, line_array[i]).c_str());
    j++;
  }
  terminal_layer(12);
  terminal_printf(x + 3 + 14, 10, "%d / %d", current_value, max_value);
  terminal_layer(2);
}

void PlayerStatusSystem::PrintStatusBarSprites(const int& x, const int& max_value, const int& current_value,
                                               const std::string& color) {
  terminal_layer(11);
  const int length_of_line = 41;
  const int length_of_array = length_of_line + 2;
  char line_array[length_of_array];  // NOLINT

  int sprite;
  int sprite_big;
  int sprite_border;
  if (color == "red") {
    sprite = 0xE111;
    sprite_big = 0xE112;
    sprite_border = 0xE113;
  }

  line_array[0] = '(';
  line_array[length_of_array - 1] = ')';

  for (int i = 1; i < length_of_array - 1; ++i) {
    line_array[i] = '-';
  }

  double percent = current_value * length_of_line / max_value;

  for (int i = 1; i <= static_cast<int>(percent); ++i) {
    if (i != length_of_array - 1) {
      line_array[i] = '|';
    }
  }

  int dx[4] = {-12, -4, 4, 12};

  for (int i = 0; i < length_of_array; ++i) {
    terminal_layer(i % 4 + 11);
    if (line_array[i] == '|') {
      terminal_put_ext(x + 1 + (i / 4), 6, dx[i % 4], 8, sprite);
    }
    if (line_array[i] == '(' || line_array[i] == ')') {
      terminal_put_ext(x + 1 + (i / 4), 6, dx[i % 4], 8, sprite_big);
    }
    if (line_array[i] == '-') {
      terminal_put_ext(x + 1 + (i / 4), 6, dx[i % 4], 8, sprite_border);
    }
  }

  std::string str = std::to_string(current_value) + " / " + std::to_string(max_value);
  for (int i = 0; i < str.size(); ++i) {
    terminal_layer(i % 4 + 15);
    terminal_put_ext(x + 2 + (i / 4), 6, dx[i % 4], 0, str.c_str()[i]);
  }
  terminal_layer(2);
}

void PlayerStatusSystem::OnUpdateText() {
  for (auto& player_entity : GetEntityManager()) {
    if (player_entity.Contains<PositionComponent>() && player_entity.Contains<PlayerComponent>()) {
      auto health = player_entity.Get<HealthComponent>();
      auto status_wallet = player_entity.Get<PlayerComponent>()->wallet_;
      auto status_turn = player_entity.Get<PlayerComponent>()->turn_;
      auto status_turns_left = player_entity.Get<PlayerComponent>()->turns_left_;
      auto status_key = player_entity.Get<PlayerComponent>()->key_count_;
      auto status_potion = player_entity.Get<PlayerComponent>()->potion_count_;
      auto stats_comp = player_entity.Get<StatsComponent>();
      static int initial_turns_left = status_turns_left;
      int box_x_size = (terminal_state(TK_WIDTH) - 30);
      terminal_printf(box_x_size + 2, 7, "[color=red]СИЛ: %d[/color]", stats_comp->strength_);
      terminal_printf(box_x_size + 11, 7, "[color=darker green]ЛОВ: %d", stats_comp->agility_);
      terminal_printf(box_x_size + 20, 7, "[color=steel]БРН: %d[/color]", stats_comp->armor_);
      terminal_printf(box_x_size + 3, 8, "Монеты: %d", status_wallet);
      terminal_printf(box_x_size + 17, 8, "Ходы: %d\n", status_turn);
      terminal_printf(box_x_size + 5, 9, "Ходов осталось: ");
      if (status_turns_left < (initial_turns_left / 2)) {
        terminal_printf(box_x_size + 21, 9, "[color=red]%d\n[/color]", status_turns_left);
      } else {
        terminal_printf(box_x_size + 21, 9, "%d\n", status_turns_left);
      }
      PrintStatusBar(box_x_size, health->maximum_health_, health->current_health_, "red");
      terminal_printf(box_x_size + 3, 11, "Ключи: [color=orange]%d\n[/color]", status_key);
      terminal_printf(box_x_size + 17, 11, "Зелья: [color=pink]%d\n[/color]", status_potion);
    }
  }
}

void PlayerStatusSystem::PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str,
                                           const std::string& color) {
  int dx[4] = {-12, -4, 4, 12};

  if (dy > 0) {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 6);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
      if (color != "white") {
        std::string colored = "[color=pink]" + str.substr(i, 1) + "[/color]";
        terminal_printf_ext(x + 1 + (i / 4), y, dx[i % 4], dy, TK_ALIGN_CENTER, colored.c_str());
      }
    }
  } else {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 2);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
    }
  }
  terminal_layer(2);
}

void PlayerStatusSystem::OnUpdateSprites() {
  for (auto& player_entity : GetEntityManager()) {
    if (player_entity.Contains<PositionComponent>() && player_entity.Contains<PlayerComponent>()) {
      auto status_wallet = player_entity.Get<PlayerComponent>()->wallet_;
      auto status_turn = player_entity.Get<PlayerComponent>()->turn_;
      auto status_turns_left = player_entity.Get<PlayerComponent>()->turns_left_;
      auto stats_comp = player_entity.Get<StatsComponent>();
      static int initial_turns_left = status_turns_left;
      int box_x_size = (terminal_state(TK_WIDTH) - 12);
      std::string str;
      str = "Money: " + std::to_string(status_wallet);
      PrintParcedString(box_x_size + 1, 7, -4, str);
      str = "Turn: " + std::to_string(status_turn);
      PrintParcedString(box_x_size + 4, 7, -4, str);
      str = "Turns left: " + std::to_string(status_turns_left);
      PrintParcedString(box_x_size + 1, 7, 12, str);
      str = "STR: " + std::to_string(stats_comp->strength_);
      PrintParcedString(box_x_size + 7, 7, -4, str);
      str = "AGI: " + std::to_string(stats_comp->agility_);
      PrintParcedString(box_x_size + 7, 7, 12, str);
      str = "ARM: " + std::to_string(stats_comp->armor_);
      PrintParcedString(box_x_size + 7, 8, -4, str);



      PrintStatusBarSprites(box_x_size, player_entity.Get<HealthComponent>()->maximum_health_,
                            player_entity.Get<HealthComponent>()->current_health_, "red");
      str = "[color=pink]" + std::to_string(player_entity.Get<PlayerComponent>()->potion_count_) + "[/color]";
      terminal_put_ext(box_x_size + 5, 9, 16, 16, 0xE014);
      terminal_print(box_x_size + 6, 9, "[color=pink]h[/color]");
      terminal_put_ext(box_x_size + 8, 9, 16, 16, 0xE015);
      terminal_print(box_x_size + 6, 10, str.c_str());
      str = "[color=orange]" + std::to_string(player_entity.Get<PlayerComponent>()->key_count_) + "[/color]";
      terminal_print(box_x_size + 9, 10, str.c_str());
    }
  }
}

void PlayerStatusSystem::OnUpdate() {
  if (datatransmitter_->IsGraphicsOn) {
    OnUpdateSprites();
  } else {
    OnUpdateText();
  }
}
void PlayerStatusSystem::OnPreUpdate() {
  terminal_clear();
}
void PlayerStatusSystem::OnPostUpdate() {
  terminal_refresh();
}
PlayerStatusSystem::PlayerStatusSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                       int loading_order)
    : ISystem(entity_manager, system_manager, loading_order) {}

PlayerStatusSystem::PlayerStatusSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                       int loading_order, DataTransmitter* datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}
