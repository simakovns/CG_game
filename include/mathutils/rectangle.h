//
// Created by simakov on 15.08.2020.
//

#ifndef INCLUDE_MATHUTILS_RECTANGLE_H_
#define INCLUDE_MATHUTILS_RECTANGLE_H_

class Rectangle {
 public:
  int x_, y_, width_, height_;

  Rectangle();

  Rectangle(int x, int y, int width, int height);

  Rectangle(const Rectangle &r);

  Rectangle &operator=(const Rectangle &other);

  friend bool operator==(const Rectangle &lhs, const Rectangle &rhs);

  friend bool operator!=(const Rectangle &lhs, const Rectangle &rhs);
};

#endif  // INCLUDE_MATHUTILS_RECTANGLE_H_
