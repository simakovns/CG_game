
#include <mathutils/pair.h>

Pair::Pair() {
  first_ = 0;
  second_ = 0;
}
Pair::Pair(const int& first, const int& second) : first_(first), second_(second) {}
Pair::Pair(const Pair& p) : first_(p.first_), second_(p.second_) {}

Pair& Pair::operator()(const int& first, const int& second) {
  first_ = first;
  second_ = second;
}

Pair& Pair::operator+=(const Pair& rhs) {
  this->first_ += rhs.first_;
  this->second_ += rhs.second_;
  return *this;
}

Pair operator+(const Pair& lhs, const Pair& rhs) {
  Pair result;
  result.first_ = lhs.first_ + rhs.first_;
  result.second_ = lhs.second_ + rhs.second_;
  return result;
}

Pair operator-(const Pair& lhs, const Pair& rhs) {
  Pair result;
  result.first_ = lhs.first_ - rhs.first_;
  result.second_ = lhs.second_ - rhs.second_;
  return result;
}

bool operator==(const Pair& lhs, const Pair& rhs) {
  if ((lhs.first_ == rhs.first_) && (lhs.second_ == rhs.second_)) {
    return true;
  } else {
    return false;
  }
}

bool operator!=(const Pair& lhs, const Pair& rhs) {
  return !(lhs == rhs);
}
