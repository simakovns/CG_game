//
// Created by simakov on 15.08.2020.
//

#ifndef INCLUDE_MATHUTILS_LEAF_H_
#define INCLUDE_MATHUTILS_LEAF_H_

#include <mathutils/rand.h>
#include <mathutils/rectangle.h>

#include <vector>
#include <cmath>
#include <iostream> // NOLINT

class Leaf {
  const int MIN_LEAF_SIZE = 12;

 public:
  int x_, y_, width_, height_;
  int rect_x, rect_y, rect_width, rect_height;
  Rectangle room;
  std::vector<Rectangle> halls;
  Rectangle null_room = Rectangle(0, 0, 0, 0);
  Leaf *leftleaf;
  Leaf *rightleaf;

  bool split();

  void createRooms();

  Rectangle GetRoom();

  void CreateHall(Rectangle l, Rectangle r);

  Leaf(int x, int y, int width, int height);
  Leaf() = default;
  Leaf(const Leaf& l) {
    x_ = l.x_;
    y_ = l.y_;
    width_ = l.width_;
    height_ = l.height_;
    leftleaf = l.leftleaf;
    rightleaf = l.rightleaf;
  }
  ~Leaf() = default;
};

#endif  // INCLUDE_MATHUTILS_LEAF_H_
