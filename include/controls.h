#ifndef INCLUDE_CONTROLS_H_
#define INCLUDE_CONTROLS_H_
#include <mathutils/pair.h>

class Controls {
 private:
  bool is_exit_ = false;
  bool move_direction_changed_ = false;
  Pair move_direction_;
  bool is_pressed_enter_ = false;
  bool is_pressed_h_ = false;
  bool is_pressed_u_ = false;

 public:
  bool Get_is_exit() const;
  bool Get_is_changed() const;
  void Set_is_changed(const bool set_change);
  bool Get_is_pressed_enter() const;
  bool Get_is_pressed_h() const;
  bool Get_is_pressed_u() const;

  Pair Get_move_direction() const;

  void Update();
  void Refresh();
};

#endif  // INCLUDE_CONTROLS_H_
