#include <BearLibTerminal.h>
#include <controls.h>
#include <scenes/character_select.h>
#include <scenes/game_over.h>
#include <scenes/game_scene.h>
#include <scenes/main_menu.h>
#include <scenes/scene_manager.h>
#include <systems/data_transmitter.h>

#include <string>

void Fill_SM_and_LevelArray(const std::string& str, DataTransmitter* DT, SceneManager* SM, const Controls& controls,
                            Context* const ctx) {
  if (str == "game_over") {
    SM->Put(str, new GameOverScene(ctx, controls, DT));
    DT->FillLevelArray(str);
  } else if (str == "main_menu") {
    SM->Put(str, new MainMenuScene(ctx, controls, DT));
    DT->FillLevelArray(str);
  } else if (str == "character_select") {
    SM->Put(str, new CharacterSelectScene(ctx, controls, DT));
    DT->FillLevelArray(str);
  } else {
    SM->Put(str, new GameScene(ctx, controls, DT));
    DT->FillLevelArray(str);
  }
}

int main() {
  terminal_open();
  terminal_set("window: size=100x30, resizeable='true', cellsize=8x16;");
  terminal_set("palette.steel = #CACCCE");
  terminal_set("palette.brown = #964B00");
  terminal_set("palette.pink = #FF69B4");
  terminal_refresh();

  Context ctx{};
  SceneManager sm(ctx);

  Controls controls;
  DataTransmitter datatransmitter;

  Fill_SM_and_LevelArray("main_menu", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("character_select", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("first_level", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("second_level", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("third_level", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("fourth_level", &datatransmitter, &sm, controls, &ctx);
  Fill_SM_and_LevelArray("game_over", &datatransmitter, &sm, controls, &ctx);

  terminal_set("0x1000: resources/fonts/a.png, resize=32x32");
  terminal_set("0x1001: resources/fonts/b.png, resize=32x32");
  terminal_set("0x1002: resources/fonts/c.png, resize=32x32");
  terminal_set("0x1003: resources/fonts/d.png, resize=32x32");
  terminal_set("0x1004: resources/fonts/e.png, resize=32x32");
  terminal_set("0x1005: resources/fonts/f.png, resize=32x32");
  terminal_set("0x1006: resources/fonts/g.png, resize=32x32");
  terminal_set("0x1007: resources/fonts/h.png, resize=32x32");
  terminal_set("0x1008: resources/fonts/i.png, resize=32x32");
  terminal_set("0x1009: resources/fonts/j.png, resize=32x32");
  terminal_set("0x1010: resources/fonts/k.png, resize=32x32");
  terminal_set("0x1011: resources/fonts/l.png, resize=32x32");
  terminal_set("0x1012: resources/fonts/m.png, resize=32x32");
  terminal_set("0x1013: resources/fonts/n.png, resize=32x32");
  terminal_set("0x1014: resources/fonts/o.png, resize=32x32");
  terminal_set("0x1015: resources/fonts/p.png, resize=32x32");
  terminal_set("0x1016: resources/fonts/q.png, resize=32x32");
  terminal_set("0x1017: resources/fonts/r.png, resize=32x32");
  terminal_set("0x1018: resources/fonts/s.png, resize=32x32");
  terminal_set("0x1019: resources/fonts/t.png, resize=32x32");
  terminal_set("0x1020: resources/fonts/u.png, resize=32x32");
  terminal_set("0x1021: resources/fonts/v.png, resize=32x32");
  terminal_set("0x1022: resources/fonts/w.png, resize=32x32");
  terminal_set("0x1023: resources/fonts/x.png, resize=32x32");
  terminal_set("0x1024: resources/fonts/y.png, resize=32x32");
  terminal_set("0x1025: resources/fonts/z.png, resize=32x32");
  terminal_set("0x1026: resources/fonts/arrow.png, resize=32x32");

  terminal_set("0xE001: resources/sprites/warrior.png, resize=32x32");
  terminal_set("0xE002: resources/sprites/ten.png, resize=32x32");
  terminal_set("0xE003: resources/sprites/dirtroad.png, resize=32x32");
  terminal_set("0xE004: resources/sprites/closedoor.png, resize=32x32");
  terminal_set("0xE005: resources/sprites/wall.png, resize=32x32");
  terminal_set("0xE006: resources/sprites/water.png, resize=32x32");
  terminal_set("0xE007: resources/sprites/box.png, resize=32x32");
  terminal_set("0xE008: resources/characters/pal.jpg, resize=320x192");
  terminal_set("0xE009: resources/sprites/tree3.png, resize=32x32");
  terminal_set("0xE010: resources/sprites/grass.png, resize=32x32");
  terminal_set("0xE012: resources/sprites/chest.png, resize=32x32");
  terminal_set("0xE013: resources/sprites/empty_chest.png, resize=32x32");
  terminal_set("0xE014: resources/sprites/potion.png, resize=32x32");
  terminal_set("0xE015: resources/sprites/key.png, resize=32x32");
  terminal_set("0xE016: resources/sprites/wanderer.png, resize=32x32");
  terminal_set("0xE017: resources/sprites/guard.png, resize=32x32");
  terminal_set("0xE018: resources/sprites/potion.png, resize=64x64");
  terminal_set("0xE019: resources/sprites/stoneroad.png, resize=64x64");
  terminal_set("0xE020: resources/sprites/bridge.png, resize=32x32");
  terminal_set("0xE021: resources/sprites/mountain.png, resize=32x32");

  terminal_set("0xE101: resources/sprites/ui/top_left.png, resize=32x32");
  terminal_set("0xE102: resources/sprites/ui/horizontal.png, resize=32x32");
  terminal_set("0xE103: resources/sprites/ui/top_right.png, resize=32x32");
  terminal_set("0xE104: resources/sprites/ui/bot_left.png, resize=32x32");
  terminal_set("0xE105: resources/sprites/ui/bot_right.png, resize=32x32");
  terminal_set("0xE106: resources/sprites/ui/switch_left.png, resize=32x32");
  terminal_set("0xE107: resources/sprites/ui/switch_right.png, resize=32x32");
  terminal_set("0xE108: resources/sprites/ui/vertical.png, resize=32x32");
  terminal_set("0xE109: resources/sprites/ui/top_switch.png, resize=32x32");
  terminal_set("0xE110: resources/sprites/ui/bot_switch.png, resize=32x32");
  terminal_set("0xE111: resources/sprites/ui/red_status_bar.png, resize=8x16");
  terminal_set("0xE112: resources/sprites/ui/red_status_bar_big.png, resize=8x16");
  terminal_set("0xE113: resources/sprites/ui/red_status_bar_border.png, resize=8x16");
  terminal_set("0xE114: resources/sprites/ui/ui_background.png, resize=32x32");
  terminal_set("0xE115: resources/sprites/ui/item_slot.png, resize=64x64");
  terminal_set("0xE116: resources/sprites/ui/ui_slot.png, resize=320x64");

  terminal_set("0xE117: resources/sprites/ui/top_left_silver.png, resize=32x32");
  terminal_set("0xE118: resources/sprites/ui/top_right_silver.png, resize=32x32");
  terminal_set("0xE119: resources/sprites/ui/bot_left_silver.png, resize=32x32");
  terminal_set("0xE120: resources/sprites/ui/bot_right_silver.png, resize=32x32");
  terminal_set("0xE121: resources/sprites/ui/horizontal_silver.png, resize=32x32");
  terminal_set("0xE122: resources/sprites/ui/vertical_silver.png, resize=32x32");

  terminal_set("0xE123: resources/sprites/ui/top_left_brown.png, resize=32x32");
  terminal_set("0xE124: resources/sprites/ui/top_right_brown.png, resize=32x32");
  terminal_set("0xE125: resources/sprites/ui/bot_left_brown.png, resize=32x32");
  terminal_set("0xE126: resources/sprites/ui/bot_right_brown.png, resize=32x32");
  terminal_set("0xE127: resources/sprites/ui/horizontal_brown.png, resize=32x32");
  terminal_set("0xE128: resources/sprites/ui/vertical_brown.png, resize=32x32");

  terminal_set("0xE201: resources/characters/warrior.png, resize=192x320");
  terminal_set("0xE202: resources/characters/duelant.png, resize=192x320");
  terminal_set("0xE203: resources/characters/shieldbearer.png, resize=192x320");
  terminal_set("0xE204: resources/characters/sword.png, resize=320x160");
  terminal_set("0xE205: resources/characters/rapier.png, resize=320x160");
  terminal_set("0xE206: resources/characters/shield.png, resize=320x160");

  terminal_set("0xE301: resources/skills/slaughter.png, resize=60x60");
  terminal_set("0xE302: resources/skills/bash.png, resize=60x60");
  terminal_set("0xE303: resources/skills/poison.png, resize=60x60");
  terminal_set("0xE304: resources/skills/ready.png, resize=64x64");
  terminal_set("0xE305: resources/skills/not_ready.png, resize=64x64");
  terminal_set("0xE306: resources/skills/stunned.png, resize=32x32");
  terminal_set("0xE307: resources/skills/poisoned.png, resize=32x32");

  ctx.scene_ = "main_menu";
  datatransmitter.SetCurrentLevel(1);
  datatransmitter.maximum_health_ = 100;
  datatransmitter.current_health_ = 100;
  datatransmitter.turns_left_ = 1000;

  static int current_window_size_x = terminal_state(TK_WIDTH);
  static int current_window_size_y = terminal_state(TK_HEIGHT);

  datatransmitter.IsGraphicsOn = true;

  if (datatransmitter.IsGraphicsOn) {
    terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
    terminal_set("window: size=40x20, resizeable='true', cellsize=32x32;");
  } else {
    terminal_set("font: resources/fonts/ubuntu-mono_R.ttf, size=8x16;");
    terminal_set("window: size=100x30, resizeable='true', cellsize=8x16;");
  }

  terminal_refresh();
  sm.OnRender();
  terminal_layer(2);
  while (true) {
    controls.Update();

    if (current_window_size_x != terminal_state(TK_WIDTH) || current_window_size_y != terminal_state(TK_HEIGHT)) {
      terminal_clear();
      sm.OnRender();
      terminal_refresh();
      current_window_size_x = terminal_state(TK_WIDTH);
      current_window_size_y = terminal_state(TK_HEIGHT);
      std::string pic_size =
          std::to_string(current_window_size_x * 32) + "x" + std::to_string(current_window_size_y * 32);
      std::string set_string = "0xE011: resources/backgrounds/castle.png, resize=" + pic_size;
      terminal_set(set_string.c_str());
    }

    if (ctx.scene_ == "game_over") {
      if (controls.Get_is_exit()) {
        break;
      }
      terminal_clear();
      sm.OnRender();
      terminal_refresh();
      if (controls.Get_is_pressed_enter()) {
        ctx.scene_ = "main_menu";
        datatransmitter.SetCurrentLevel(1);
      }
      controls.Refresh();
    } else if (ctx.scene_ == "main_menu" || ctx.scene_ == "character_select") {
      if (controls.Get_is_exit()) {
        break;
      }
      terminal_clear();
      sm.OnRender();
      controls.Refresh();
      terminal_refresh();
    } else if (ctx.scene_ != sm.GetCurrentScene()) {
      terminal_clear();
      sm.OnRender();
      terminal_refresh();
    } else {
      if (controls.Get_is_exit()) {
        break;
      }
      if (controls.Get_is_changed()) {
        terminal_clear();
        sm.OnRender();
        terminal_refresh();
        controls.Set_is_changed(false);
        controls.Refresh();
      }
    }
    if (datatransmitter.OnExit) {
      break;
    }
  }
  sm.OnExit();
  terminal_close();
}
