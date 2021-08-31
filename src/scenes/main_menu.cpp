//
// Created by simakov on 17.07.2020.
//

#include <BearLibTerminal.h>
#include <components/all_components.h>
#include <ecs/engine.h>
#include <levels/char_file_reader.h>
#include <scenes/main_menu.h>
#include <systems/all_systems.h>

#include <vector>
#include <string>

void MainMenuScene::OnCreate() {}


void MainMenuScene::OnCreateText() {
  int box_x_size = (terminal_state(TK_WIDTH)) / 2 - 5;
  int box_y_size = terminal_state(TK_HEIGHT) / 2 - 5;
  terminal_print(box_x_size, box_y_size, "New game");
  terminal_print(box_x_size, box_y_size + 1, "Graphics: ");
  terminal_print(box_x_size + 10, box_y_size + 1, "off");
  terminal_print(box_x_size, box_y_size + 2, "Exit");

  if (datatransmitter_->menu_cursor == 1) {
    terminal_put(box_x_size - 1, box_y_size, '>');
    if (controls.Get_is_pressed_enter()) {
      ctx_->scene_ = "character_select";
      datatransmitter_->SetCurrentLevel(2);
    }
  }

  if (datatransmitter_->menu_cursor == 2) {
    terminal_put(box_x_size - 1, box_y_size + 1, '>');
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->IsGraphicsOn = !datatransmitter_->IsGraphicsOn;
      if (datatransmitter_->IsGraphicsOn) {
        terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
        terminal_set("window: size=40x20, cellsize=32x32;");
      } else {
        terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
        terminal_set("window: size=100x30, cellsize=8x16;");
      }
    }
  }

  if (datatransmitter_->menu_cursor == 3) {
    terminal_put(box_x_size - 1, box_y_size + 2, '>');
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->OnExit = true;
    }
  }
}
void MainMenuScene::OnCreateSprites() {
  int box_x_size = (terminal_state(TK_WIDTH)) / 2;
  int box_y_size = terminal_state(TK_HEIGHT) / 2;

  terminal_put(0, 0, 0xE011);

  // New game
  terminal_put(box_x_size - 4, box_y_size, 0x1013);
  terminal_put(box_x_size - 3, box_y_size, 0x1004);
  terminal_put(box_x_size - 2, box_y_size, 0x1022);
  terminal_put(box_x_size, box_y_size, 0x1006);
  terminal_put(box_x_size + 1, box_y_size, 0x1000);
  terminal_put(box_x_size + 2, box_y_size, 0x1012);
  terminal_put(box_x_size + 3, box_y_size, 0x1004);

  // Graphics
  terminal_put(box_x_size - 4, box_y_size + 1, 0x1006);
  terminal_put(box_x_size - 3, box_y_size + 1, 0x1017);
  terminal_put(box_x_size - 2, box_y_size + 1, 0x1000);
  terminal_put(box_x_size - 1, box_y_size + 1, 0x1015);
  terminal_put(box_x_size, box_y_size + 1, 0x1007);
  terminal_put(box_x_size + 1, box_y_size + 1, 0x1008);
  terminal_put(box_x_size + 2, box_y_size + 1, 0x1002);
  terminal_put(box_x_size + 3, box_y_size + 1, 0x1018);

  // on
  terminal_put(box_x_size + 6, box_y_size + 1, 0x1014);
  terminal_put(box_x_size + 7, box_y_size + 1, 0x1013);

  // Exit
  terminal_put(box_x_size - 4, box_y_size + 2, 0x1004);
  terminal_put(box_x_size - 3, box_y_size + 2, 0x1023);
  terminal_put(box_x_size - 2, box_y_size + 2, 0x1008);
  terminal_put(box_x_size - 1, box_y_size + 2, 0x1019);

  if (datatransmitter_->menu_cursor == 1) {
    terminal_put(box_x_size - 5, box_y_size, 0x1026);
    if (controls.Get_is_pressed_enter()) {
      ctx_->scene_ = "character_select";
      datatransmitter_->SetCurrentLevel(2);
    }
  }

  if (datatransmitter_->menu_cursor == 2) {
    terminal_put(box_x_size - 5, box_y_size + 1, 0x1026);
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->IsGraphicsOn = !datatransmitter_->IsGraphicsOn;
      if (datatransmitter_->IsGraphicsOn) {
        terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
        terminal_set("window: size=40x20, cellsize=32x32;");
      } else {
        terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
        terminal_set("window: size=100x30, cellsize=8x16;");
      }
    }
  }

  if (datatransmitter_->menu_cursor == 3) {
    terminal_put(box_x_size - 5, box_y_size + 2, 0x1026);
    if (controls.Get_is_pressed_enter()) {
      datatransmitter_->OnExit = true;
    }
  }
}
void MainMenuScene::OnRender() {
  if (controls.Get_move_direction() == DOWN && datatransmitter_->menu_cursor < 3) {
    datatransmitter_->menu_cursor++;
  } else if (controls.Get_move_direction() == UP && datatransmitter_->menu_cursor > 1) {
    datatransmitter_->menu_cursor--;
  }

  if (datatransmitter_->IsGraphicsOn) {
    OnCreateSprites();
  } else {
    OnCreateText();
  }

  engine.OnUpdate();
}
void MainMenuScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
MainMenuScene::MainMenuScene(Context* const ctx, const Controls& controls) : Scene(ctx), controls(controls) {}
MainMenuScene::MainMenuScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter)
    : Scene(ctx), controls(controls), datatransmitter_(datatransmitter) {}
