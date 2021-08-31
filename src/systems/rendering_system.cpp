//
// Created by simakov on 17.07.2020.
//
#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <ecs/entity_manager.h>
#include <levels/char_file_reader.h>
#include <systems/rendering_system.h>

#include <cmath>
#include <iostream>  // NOLINT
#include <string>
#include <vector>

std::string RenderingSystem::GetColoredSymbol(const std::string& color, const char& symbol) {
  std::string color_ = "[color=" + color + "]";
  std::string symbol_to_string(1, symbol);
  return (color_ + symbol_to_string + "[/color]");
}

void RenderingSystem::RenderBackgroundOnFirstLevel(const int& x_1, const int& x_2, const int& y_1, const int& y_2,
                                                   const int& box_x_size, const int& box_y_size, const int& sprite) {
  if (datatransmitter_->current_level == "first_level" && datatransmitter_->IsGraphicsOn) {
    terminal_layer(0);
    for (int y = y_1; y < y_2; ++y) {
      for (int x = x_1 + 1; x < x_2; ++x) {
        terminal_put(x, y, sprite);
      }
    }
  }
}

void RenderingSystem::RenderBackground(const int& x_1, const int& x_2, const int& y_1, const int& y_2,
                                       const int& sprite) {}

void RenderingSystem::RenderCharacter(const std::string& character_name, const int& box_x_size) {
  const char backslash = static_cast<char>(92);

  CharFileReader reader(character_name);
  reader.Read();
  std::vector<std::vector<char>> res = reader.GetResourceMatrix();
  for (int y = 0; y < res.size(); ++y) {
    for (int x = 0; x < res[y].size(); ++x) {
      if ((res[y][x] == '(') || (res[y][x] == ')')) {
        std::string color = "red";
        terminal_print(x + box_x_size + 1, y + 1, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if (res[y][x] == '=') {
        std::string color = "flame";
        terminal_print(x + box_x_size + 1, y + 1, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if ((res[y][x] == '/') || (res[y][x] == backslash) || (res[y][x] == '|')) {
        std::string color = "red";
        terminal_print(x + box_x_size + 1, y + 1, GetColoredSymbol(color, (res[y][x])).c_str());
      }
      if ((res[y][x] == ':') || (res[y][x] == '>') || (res[y][x] == '{') || (res[y][x] == '-')) {
        std::string color = "steel";
        terminal_print(x + box_x_size + 1, y + 1, GetColoredSymbol(color, (res[y][x])).c_str());
      }
    }
  }
}

void RenderingSystem::RenderBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2) {
  for (int y = y_1; y < y_2; ++y) {
    terminal_put(x_2, y, '|');
  }

  for (int y = y_1; y < y_2; ++y) {
    terminal_put(x_1, y, '|');
  }
  for (int x = x_1 + 1; x < x_2; ++x) {
    terminal_put(x, y_1, '=');
  }
  for (int x = 1; x < x_2; ++x) {
    terminal_put(x, y_2 - 1, '=');
  }
}

void RenderingSystem::RenderSpriteBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2) {
  terminal_put(x_1, y_1, 0xE101);
  terminal_put(x_1, y_2 - 1, 0xE104);

  for (int y = y_1 + 1; y < y_2 - 1; ++y) {
    terminal_put(x_1, y, 0xE108);
  }

  for (int x = x_1 + 1; x < x_2; ++x) {
    terminal_put(x, y_1, 0xE102);
    terminal_put(x, y_2 - 1, 0xE102);
  }
}

void RenderingSystem::RenderInterface(const std::string& character_name, const int& box_x_size) {
  for (int x = box_x_size + 1; x < box_x_size + 28; ++x) {
    terminal_put(x, 0, '=');
  }
  for (int x = box_x_size + 1; x < box_x_size + 28; ++x) {
    terminal_put(x, 6, '=');
  }
  for (int y = 0; y < 7; ++y) {
    terminal_put(box_x_size + 28, y, '|');
  }
  RenderCharacter(character_name, box_x_size);
}

void RenderingSystem::RenderInterfaceSprites(const int& x_1, const int& x_2, const int& y_1, const int& y_2) {
  // render borders
  terminal_layer(10);
  terminal_put(x_1 + 1, y_1, 0xE109);
  terminal_put(x_2, y_1, 0xE103);
  terminal_put(x_1 + 1, y_2 - 1, 0xE110);
  terminal_put(x_2, y_2 - 1, 0xE105);
  terminal_put(x_1 + 1, y_1 + 6, 0xE106);
  terminal_put(x_2, y_1 + 6, 0xE107);

  for (int x = x_1 + 2; x < x_2; ++x) {
    terminal_put(x, y_1, 0xE102);
  }
  for (int x = x_1 + 2; x < x_2; ++x) {
    terminal_put(x, y_2 - 1, 0xE102);
    terminal_put(x, y_1 + 6, 0xE102);
  }
  for (int y = y_1 + 1; y < 6; ++y) {
    terminal_put(x_1 + 1, y, 0xE108);
    terminal_put(x_2, y, 0xE108);
  }
  for (int y = 7; y < y_2 - 1; ++y) {
    terminal_put(x_1 + 1, y, 0xE108);
    terminal_put(x_2, y, 0xE108);
  }

  terminal_put(x_1 + 2, y_1 + 1, datatransmitter_->pic_of_character_);

  terminal_layer(2);
  // render ui
  terminal_layer(0);
  for (int x = x_1 + 2; x < x_2; ++x) {
    for (int y = 7; y < y_2 - 1; ++y) {
      terminal_put(x, y, 0xE114);
    }
  }
  terminal_layer(1);

  terminal_put(x_1 + 3, y_1 + 9, 0xE115);
  terminal_put(x_1 + 6, y_1 + 9, 0xE115);
  terminal_put(x_1 + 9, y_1 + 9, 0xE115);

  terminal_put(x_1 + 2, y_1 + 7, 0xE116);
}

void RenderingSystem::RenderWindow(const int& x_1, const int& x_2, const int& y_1, const int& y_2) {
  for (int x = x_1 - 1; x < x_2 + 1; ++x) {
    terminal_put(x - datatransmitter_->pos_.first_ + 35, y_1 - datatransmitter_->pos_.second_ + 15, '=');
  }
  for (int x = x_1 - 1; x < x_2 + 1; ++x) {
    terminal_put(x - datatransmitter_->pos_.first_ + 35, y_2 - datatransmitter_->pos_.second_ + 15, '=');
  }
}

void RenderingSystem::PrintEntities(const int& x_1, const int& x_2, const int& y_1, const int& y_2,
                                    const int& box_x_size, const int& box_y_size) {
  for (auto& e : GetEntityManager()) {
    if (e.Contains<PositionComponent>() && e.Contains<TextureComponent>()) {
      auto texture = e.Get<TextureComponent>();
      auto position = e.Get<PositionComponent>();
      if (position->pos_.first_ > x_1 && position->pos_.first_ < x_2 && position->pos_.second_ > y_1 &&
          position->pos_.second_ < y_2) {
        if (texture->layer_ != 2) {
          terminal_layer(texture->layer_);
          terminal_print(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                         position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size,
                         GetColoredSymbol(texture->color_, texture->symbol_).c_str());
          terminal_layer(2);
        } else {
          terminal_print(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                         position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size,
                         GetColoredSymbol(texture->color_, texture->symbol_).c_str());
        }
      }
    }
  }
}

void RenderingSystem::OnUpdate() {
  CharFileReader level(datatransmitter_->file_name);
  if (datatransmitter_->IsGraphicsOn) {
    int box_x_size = static_cast<int>(std::round((terminal_state(TK_WIDTH) - 12) / 2));
    int box_y_size = static_cast<int>(std::round(terminal_state(TK_HEIGHT) / 2));

    int box_x_1 = datatransmitter_->pos_.first_ - box_x_size;
    int box_x_2 = datatransmitter_->pos_.first_ + box_x_size;
    int box_y_1 = datatransmitter_->pos_.second_ - box_y_size;
    int box_y_2 = datatransmitter_->pos_.second_ + box_y_size;

    RenderBackgroundOnFirstLevel(0, box_x_size * 2, 0, box_y_size * 2, box_x_size, box_y_size, 0xE010);

    for (auto& e : GetEntityManager()) {
      if (e.Contains<PositionComponent>() && e.Contains<TextureComponent>()) {
        auto texture = e.Get<TextureComponent>();
        auto sprite = e.Get<SpriteComponent>();
        auto position = e.Get<PositionComponent>();
        if (position->pos_.first_ > box_x_1 && position->pos_.first_ < box_x_2 && position->pos_.second_ > box_y_1 &&
            position->pos_.second_ < box_y_2) {
          if (texture->layer_ != 2) {
            terminal_layer(texture->layer_);
            terminal_put(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                         position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size, sprite->sprite_);
            terminal_layer(2);
          } else {
            terminal_put(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                         position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size, sprite->sprite_);
          }
          if (e.Contains<EffectsComponent>()) {
            terminal_layer(3);
            if (e.Get<EffectsComponent>()->IsPoisoned) {
              terminal_put(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                           position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size, 0xE307);
            }
            if (e.Get<EffectsComponent>()->IsStunned_) {
              terminal_put(position->pos_.first_ - datatransmitter_->pos_.first_ + box_x_size,
                           position->pos_.second_ - datatransmitter_->pos_.second_ + box_y_size, 0xE306);
            }
            terminal_layer(2);
          }
        }
      }
    }
    RenderInterfaceSprites(box_x_size * 2 - 1, box_x_size * 2 + 11, 0, terminal_state(TK_HEIGHT));
    RenderSpriteBorders(0, box_x_size * 2, 0, box_y_size * 2);

  } else {
    int box_x_size = (terminal_state(TK_WIDTH) - 30) / 2;
    int box_y_size = terminal_state(TK_HEIGHT) / 2;

    int box_x_1 = datatransmitter_->pos_.first_ - box_x_size;
    int box_x_2 = datatransmitter_->pos_.first_ + box_x_size;
    int box_y_1 = datatransmitter_->pos_.second_ - box_y_size;
    int box_y_2 = datatransmitter_->pos_.second_ + box_y_size;

    PrintEntities(box_x_1, box_x_2, box_y_1, box_y_2, box_x_size, box_y_size);
    RenderBorders(0, (terminal_state(TK_WIDTH) - 30), 0, terminal_state(TK_HEIGHT));
    RenderInterface(datatransmitter_->GetCharacterName(), box_x_size * 2);
  }
}
void RenderingSystem::OnPreUpdate() {
  terminal_clear();
}
void RenderingSystem::OnPostUpdate() {
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                 int loading_order)
    : ISystem(entity_manager, system_manager, loading_order) {}

RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                 int loading_order, DataTransmitter* datatransmitter)
    : ISystem(entity_manager, system_manager, loading_order), datatransmitter_(datatransmitter) {}

RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                 int loading_order, DataTransmitter* datatransmitter, int number_of_level)
    : ISystem(entity_manager, system_manager, loading_order),
      datatransmitter_(datatransmitter),
      number_of_level_(number_of_level) {}
