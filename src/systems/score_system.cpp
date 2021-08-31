//
// Created by simakov on 17.07.2020.
//
#include <BearLibTerminal.h>
#include <ecs/entity_manager.h>
#include <systems/data_transmitter.h>
#include <systems/score_system.h>

#include <string>

void ScoreSystem::PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str) {
  int dx[4] = {-12, -4, 4, 12};

  if (dy > 0) {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 6);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
    }
  } else {
    for (int i = 0; i < str.size(); ++i) {
      terminal_layer(i % 4 + 2);
      terminal_put_ext(x + 1 + (i / 4), y, dx[i % 4], dy, str.c_str()[i]);
    }
  }
  terminal_layer(2);
}

void ScoreSystem::OnCreateSprites() {
  int box_x_size = terminal_state(TK_WIDTH) / 2 - 10;
  int box_y_size = terminal_state(TK_HEIGHT) / 3;
  if (datatransmitter_->turns_left_ == 0) {
    PrintParcedString(box_x_size - 1, box_y_size, -8, "The end...");
    PrintParcedString(box_x_size - 1, box_y_size, 8, "No more turns...");
  } else if (datatransmitter_->current_health_ <= 0) {
    PrintParcedString(box_x_size - 1, box_y_size, -8, "The end...");
    PrintParcedString(box_x_size - 1, box_y_size, 8, "You died...");
  } else {
    PrintParcedString(box_x_size - 1, box_y_size, -8, "The end...");
    PrintParcedString(box_x_size - 1, box_y_size, -8, "You won!");
  }
  std::string str = "You gathered " + std::to_string(datatransmitter_->wallet_) + " coins";
  PrintParcedString(box_x_size - 1, box_y_size + 1, -8, str);
  str = "You've made " + std::to_string(datatransmitter_->turn_) + " turns";
  PrintParcedString(box_x_size - 1, box_y_size + 1, 8, str);

  PrintParcedString(box_x_size - 1, box_y_size + 2, 0, "Press enter to begin new game");
}

void ScoreSystem::OnCreateText() {
  int box_x_size = terminal_state(TK_WIDTH) / 2 - 10;
  int box_y_size = terminal_state(TK_HEIGHT) / 5;

  if (datatransmitter_->turns_left_ == 0) {
    terminal_print(box_x_size - 1, box_y_size, "The end...");
    terminal_print(box_x_size - 1, box_y_size + 1, "No more turns...");
  } else if (datatransmitter_->current_health_ <= 0) {
    terminal_print(box_x_size - 1, box_y_size, "The end...");
    terminal_print(box_x_size - 1, box_y_size + 1, "You died...");
  } else {
    terminal_print(box_x_size - 1, box_y_size, "The end...");
    terminal_print(box_x_size - 1, box_y_size + 1, "You won!");
  }

  terminal_printf(box_x_size - 1, box_y_size + 2, "You gathered: %d coins", (datatransmitter_->wallet_));
  terminal_printf(box_x_size - 1, box_y_size + 3, "You've made %d turns", (datatransmitter_->turn_));
  terminal_print(box_x_size - 1, box_y_size + 4, "Press enter to begin new game.");
}

void ScoreSystem::OnUpdate() {
  if (datatransmitter_->IsGraphicsOn) {
    OnCreateSprites();
  } else {
    OnCreateText();
  }
}
void ScoreSystem::OnPreUpdate() {
  terminal_clear();
}
void ScoreSystem::OnPostUpdate() {
  terminal_refresh();
}
ScoreSystem::ScoreSystem(EntityManager* const entity_manager, SystemManager* const system_manager, int loading_order)
    : ISystem(entity_manager, system_manager, loading_order) {}

ScoreSystem::ScoreSystem(EntityManager* const entity_manager, SystemManager* const system_manager, int loading_order,
                         DataTransmitter* datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}
