//
// Created by simakov on 15.08.2020.
//

#include <mathutils/rectangle.h>

Rectangle::Rectangle() {
  x_ = 0;
  y_ = 0;
  width_ = 0;
  height_ = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {}

Rectangle::Rectangle(const Rectangle &r) : x_(r.x_), y_(r.y_), width_(r.width_), height_(r.height_) {}

Rectangle& Rectangle::operator=(const Rectangle &other) {
  if (this != &other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    this->width_ = other.width_;
    this->height_ = other.height_;
  }
}

bool operator==(const Rectangle &lhs, const Rectangle &rhs) {
  if ((lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_) && (lhs.width_ == rhs.width_) && (lhs.height_ == rhs.height_)) {
    return true;
  } else {
    return false;
  }
}

bool operator!=(const Rectangle &lhs, const Rectangle &rhs) {
  return !(lhs == rhs);
}
