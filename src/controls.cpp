#include <BearLibTerminal.h>
#include <controls.h>

bool Controls::Get_is_exit() const {
  return is_exit_;
}

bool Controls::Get_is_pressed_enter() const {
  return is_pressed_enter_;
}

bool Controls::Get_is_changed() const {
  return move_direction_changed_;
}

bool Controls::Get_is_pressed_h() const {
  return is_pressed_h_;
}

bool Controls::Get_is_pressed_u() const {
  return is_pressed_u_;
}

void Controls::Set_is_changed(const bool set_change) {
  move_direction_changed_ = set_change;
}

void Controls::Refresh() {
  is_pressed_enter_ = false;
  is_pressed_h_ = false;
  is_pressed_u_ = false;
}

Pair Controls::Get_move_direction() const {
  return move_direction_;
}

void Controls::Update() {
  move_direction_(0, 0);

  while (terminal_has_input()) {
    auto command = terminal_read();
    is_pressed_enter_ = false;
    switch (command) {
      case TK_ENTER: {
        is_pressed_enter_ = true;
        move_direction_changed_ = true;
        break;
      }
      case TK_SPACE: {
        move_direction_changed_ = true;
        break;
      }
      case TK_CLOSE: {
        is_exit_ = true;
        break;
      }

      case TK_UP: {
        move_direction_ = {0, -1};
        move_direction_changed_ = true;
        break;
      }

      case TK_DOWN: {
        move_direction_ = {0, 1};
        move_direction_changed_ = true;
        break;
      }

      case TK_LEFT: {
        move_direction_ = {-1, 0};
        move_direction_changed_ = true;
        break;
      }

      case TK_RIGHT: {
        move_direction_ = {1, 0};
        move_direction_changed_ = true;
        break;
      }

      case TK_H: {
        is_pressed_h_ = true;
        move_direction_changed_ = true;
        break;
      }

      case TK_U: {
        is_pressed_u_ = true;
        move_direction_changed_ = true;
        break;
      }
      default: {
        break;
      }
    }
  }
}
