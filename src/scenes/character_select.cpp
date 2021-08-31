//
// Created by simakov on 17.07.2020.
//

#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <ecs/engine.h>
#include <levels/char_file_reader.h>
#include <scenes/character_select.h>
#include <systems/all_systems.h>

#include <iostream>  // NOLINT
#include <string>
#include <vector>

std::string CharacterSelectScene::GetColoredSymbol(const std::string& color, const char& symbol) {
  std::string color_ = "[color=" + color + "]";
  std::string symbol_to_string(1, symbol);
  return (color_ + symbol_to_string + "[/color]");
}

void CharacterSelectScene::RenderCharacter(const std::string& character_name, const int& box_x_size,
                                           const int& box_y_size) {
  const char backslash = static_cast<char>(92);

  CharFileReader reader(character_name);
  reader.Read();
  std::vector<std::vector<char>> res = reader.GetResourceMatrix();
  for (int y = 0; y < res.size(); ++y) {
    for (int x = 0; x < res[y].size(); ++x) {
      if ((res[y][x] == '(') || (res[y][x] == ')')) {
        std::string color = "red";
        terminal_print(x + box_x_size + 1, y + 1 + box_y_size, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if (res[y][x] == '=') {
        std::string color = "flame";
        terminal_print(x + box_x_size + 1, y + 1 + box_y_size, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if ((res[y][x] == '/') || (res[y][x] == backslash) || (res[y][x] == '|')) {
        std::string color = "red";
        terminal_print(x + box_x_size + 1, y + 1 + box_y_size, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if ((res[y][x] == ':') || (res[y][x] == '>') || (res[y][x] == '{') || (res[y][x] == '-')) {
        std::string color = "steel";
        terminal_print(x + box_x_size + 1, y + 1 + box_y_size, GetColoredSymbol(color, (res[y][x])).c_str());
      }
    }
  }
}

void CharacterSelectScene::OnCreate() {}

void CharacterSelectScene::PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str) {
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

void CharacterSelectScene::PrintBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2,
                                        const bool IsSelected) {
  int top_left;
  int top_right;
  int bot_left;
  int bot_right;
  int horizontal;
  int vertical;

  if (IsSelected) {
    top_left = 0xE117;
    top_right = 0xE118;
    bot_left = 0xE119;
    bot_right = 0xE120;
    horizontal = 0xE121;
    vertical = 0xE122;
  } else {
    top_left = 0xE123;
    top_right = 0xE124;
    bot_left = 0xE125;
    bot_right = 0xE126;
    horizontal = 0xE127;
    vertical = 0xE128;
  }
  terminal_put(x_1 - 1, y_1 - 1, top_left);
  terminal_put(x_2 + 1, y_1 - 1, top_right);
  terminal_put(x_1 - 1, y_2 + 1, bot_left);
  terminal_put(x_2 + 1, y_2 + 1, bot_right);
  for (int x = x_1; x < x_2 + 1; x++) {
    terminal_put(x, y_1 - 1, horizontal);
    terminal_put(x, y_2 + 1, horizontal);
  }

  for (int y = y_1; y < y_2 + 1; ++y) {
    terminal_put(x_1 - 1, y, vertical);
    terminal_put(x_2 + 1, y, vertical);
  }
}

void CharacterSelectScene::ChooseCharacterSprite() {
  int box_x_size = (terminal_state(TK_WIDTH)) / 2;
  int box_y_size = terminal_state(TK_HEIGHT) / 4;

  terminal_layer(0);
  terminal_bkcolor("grey");
  terminal_layer(2);

  PrintParcedString(box_x_size - 7, box_y_size - 3, 0, "Choose your class and press enter to continue...");

  int x = (terminal_state(TK_WIDTH)) / 3 - 8;
  terminal_put(x, box_y_size, 0xE201);
  PrintBorders(x, x + 5, box_y_size, box_y_size + 9, false);

  x = (terminal_state(TK_WIDTH)) / 2 - 3;
  terminal_put(x, box_y_size, 0xE202);
  PrintBorders(x, x + 5, box_y_size, box_y_size + 9, false);

  x = (terminal_state(TK_WIDTH)) / 3 * 2 + 3;
  terminal_put(x, box_y_size, 0xE203);
  PrintBorders(x, x + 5, box_y_size, box_y_size + 9, false);

  if (datatransmitter_->menu_cursor == 1) {
    x = (terminal_state(TK_WIDTH)) / 3 - 8;
    PrintBorders(x, x + 5, box_y_size, box_y_size + 9, true);
    PrintParcedString(x + 1, box_y_size + 11, 0, "Knight");
    PrintParcedString(x - 3, box_y_size + 12, -8, "Base health: 100");
    PrintParcedString(x - 3, box_y_size + 12, 8, "Base damage: 20");
    PrintParcedString(x - 3, box_y_size + 13, -8, "Strength: 30");
    PrintParcedString(x - 3, box_y_size + 13, 8, "Agility: 20");
    PrintParcedString(x - 3, box_y_size + 14, -8, "Armor: 20");
    // terminal_put(x, box_y_size + 12, 0xE303);
    terminal_put_ext(x + 4, box_y_size + 13, 10, -8, 0xE303);
    PrintParcedString(x + 2, box_y_size + 12, -8, "Spec. ability: Poison");

    datatransmitter_->current_health_ = 100;
    datatransmitter_->maximum_health_ = 100;
    datatransmitter_->damage_ = 20;
    datatransmitter_->strength_ = 10;
    datatransmitter_->agility_ = 20;
    datatransmitter_->armor_ = 20;
    datatransmitter_->sprite_of_character_ = 0xE001;
    datatransmitter_->pic_of_character_ = 0xE204;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "warrior";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }

  } else if (datatransmitter_->menu_cursor == 2) {
    x = (terminal_state(TK_WIDTH)) / 2 - 3;
    PrintBorders(x, x + 5, box_y_size, box_y_size + 9, true);
    PrintParcedString(x + 1, box_y_size + 11, 0, "Dueller");
    PrintParcedString(x - 3, box_y_size + 12, -8, "Base health: 60");
    PrintParcedString(x - 3, box_y_size + 12, 8, "Base damage: 40");
    PrintParcedString(x - 3, box_y_size + 13, -8, "Strength: 40");
    PrintParcedString(x - 3, box_y_size + 13, 8, "Agility: 70");
    PrintParcedString(x - 3, box_y_size + 14, -8, "Armor: 0");
    terminal_put_ext(x + 5, box_y_size + 13, 0, -8, 0xE301);
    PrintParcedString(x + 2, box_y_size + 12, -8, "Spec. ability: Slaughter");
    datatransmitter_->current_health_ = 60;
    datatransmitter_->maximum_health_ = 60;
    datatransmitter_->damage_ = 40;
    datatransmitter_->strength_ = 40;
    datatransmitter_->agility_ = 70;
    datatransmitter_->armor_ = 0;
    datatransmitter_->sprite_of_character_ = 0xE001;
    datatransmitter_->pic_of_character_ = 0xE205;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "duelant";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }

  } else if (datatransmitter_->menu_cursor == 3) {
    x = (terminal_state(TK_WIDTH)) / 3 * 2 + 3;
    PrintBorders(x, x + 5, box_y_size, box_y_size + 9, true);
    PrintParcedString(x + 1, box_y_size + 11, 0, "Shieldbearer");
    PrintParcedString(x - 3, box_y_size + 12, -8, "Base health: 200");
    PrintParcedString(x - 3, box_y_size + 12, 8, "Base damage: 10");
    PrintParcedString(x - 3, box_y_size + 13, -8, "Strength: 60");
    PrintParcedString(x - 3, box_y_size + 13, 8, "Agility: 0");
    PrintParcedString(x - 3, box_y_size + 14, -8, "Armor: 60");
    terminal_put_ext(x + 5, box_y_size + 13, 0, -8, 0xE302);
    PrintParcedString(x + 2, box_y_size + 12, -8, "Spec. ability: Frightening");
    datatransmitter_->current_health_ = 200;
    datatransmitter_->maximum_health_ = 200;
    datatransmitter_->damage_ = 10;
    datatransmitter_->strength_ = 60;
    datatransmitter_->agility_ = 0;
    datatransmitter_->armor_ = 60;
    datatransmitter_->sprite_of_character_ = 0xE001;
    datatransmitter_->pic_of_character_ = 0xE206;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "shieldbearer";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }
  }
}

void CharacterSelectScene::OnCreateText() {}
void CharacterSelectScene::OnCreateSprites() {}

void CharacterSelectScene::OnRender() {
  if (controls.Get_move_direction() == RIGHT && datatransmitter_->menu_cursor < 3) {
    datatransmitter_->menu_cursor++;
  } else if (controls.Get_move_direction() == LEFT && datatransmitter_->menu_cursor > 1) {
    datatransmitter_->menu_cursor--;
  }

  if (datatransmitter_->IsGraphicsOn) {
    ChooseCharacterSprite();
  } else {
    ChooseCharacterText();
  }

  engine.OnUpdate();
}
void CharacterSelectScene::OnExit() {
  datatransmitter_->Refresh();
  terminal_layer(0);
  terminal_bkcolor("black");
  terminal_layer(2);
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}

void CharacterSelectScene::ChooseCharacterText() {
  int box_x_size = (terminal_state(TK_WIDTH)) / 5 - 13;
  int box_y_size = terminal_state(TK_HEIGHT) / 4;

  RenderCharacter("resources/characters/warrior.dat", box_x_size, box_y_size);
  RenderCharacter("resources/characters/duelant.dat", box_x_size + 28, box_y_size);
  RenderCharacter("resources/characters/shieldbearer.dat", box_x_size + 56, box_y_size);

  terminal_print((terminal_state(TK_WIDTH)) / 2 - 26, box_y_size - 2,
                 "Выберите персонажа и нажмите enter чтобы продолжить:");

  if (datatransmitter_->menu_cursor == 1) {
    terminal_print(box_x_size + 3, box_y_size + 6, "^^^^^^^^^^^^^^^^^^^^^^^^");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 3, box_y_size + 8, "Рыцарь");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 9, "Базовое здоровье: 100");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 10, "Базовый урон: 20");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 11, "Сила: 30");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 12, "Ловкость: 20");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 13, "Броня: 20");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 17, box_y_size + 15, "Особое умение - отрава. Пока умение");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 17, box_y_size + 16, "активно, атаки отравляют врагов.");
    datatransmitter_->current_health_ = 100;
    datatransmitter_->maximum_health_ = 100;
    datatransmitter_->damage_ = 20;
    datatransmitter_->strength_ = 10;
    datatransmitter_->agility_ = 20;
    datatransmitter_->armor_ = 20;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "warrior";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }

  } else if (datatransmitter_->menu_cursor == 2) {
    terminal_print(box_x_size + 31, box_y_size + 6, "^^^^^^^^^^^^^^^^^^^^^^^^");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 3, box_y_size + 8, "Дуэлянт");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 9, "Базовое здоровье: 60");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 10, "Базовый урон: 40");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 11, "Сила: 40");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 12, "Ловкость: 70");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 13, "Броня: 0");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 17, box_y_size + 15, "Особое умение - резня. Пока умение");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 17, box_y_size + 16, "активно, дуэлянт не получает урона");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 17, box_y_size + 17, "и шанс критического удара удваивается");
    datatransmitter_->current_health_ = 60;
    datatransmitter_->maximum_health_ = 60;
    datatransmitter_->damage_ = 40;
    datatransmitter_->strength_ = 40;
    datatransmitter_->agility_ = 70;
    datatransmitter_->armor_ = 0;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "duelant";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }

  } else if (datatransmitter_->menu_cursor == 3) {
    terminal_print(box_x_size + 59, box_y_size + 6, "^^^^^^^^^^^^^^^^^^^^^^^^");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 4, box_y_size + 8, "Щитоносец");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 9, "Базовое здоровье: 200");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 10, "Базовый урон: 10");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 11, "Сила: 60");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 12, "Ловкость: 0");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 15, box_y_size + 13, "Броня: 60");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 20, box_y_size + 15, "Особое умение - устрашение. При активации");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 20, box_y_size + 16, "умения враги в небольшом радиусе вокруг");
    terminal_print((terminal_state(TK_WIDTH)) / 2 - 14, box_y_size + 17, "щитоносца будут оглушены.");
    datatransmitter_->current_health_ = 200;
    datatransmitter_->maximum_health_ = 200;
    datatransmitter_->damage_ = 10;
    datatransmitter_->strength_ = 60;
    datatransmitter_->agility_ = 0;
    datatransmitter_->armor_ = 60;
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->character_ = "shieldbearer";
      ctx_->scene_ = "first_level";
      datatransmitter_->SetCurrentLevel(3);
    }
  }
}

CharacterSelectScene::CharacterSelectScene(Context* const ctx, const Controls& controls)
    : Scene(ctx), controls(controls) {}
CharacterSelectScene::CharacterSelectScene(Context* const ctx, const Controls& controls,
                                           DataTransmitter* datatransmitter)
    : Scene(ctx), controls(controls), datatransmitter_(datatransmitter) {}
