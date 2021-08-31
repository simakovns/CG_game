#ifndef INCLUDE_MATHUTILS_PAIR_H_
#define INCLUDE_MATHUTILS_PAIR_H_

class Pair {
 public:
  int first_;
  int second_;

  Pair();
  Pair(const int& first, const int& second);
  Pair(const Pair& p);

  Pair& operator()(const int& first, const int& second);

  Pair& operator+=(const Pair& rhs);

  friend Pair operator+(const Pair& lhs, const Pair& rhs);

  friend Pair operator-(const Pair& lhs, const Pair& rhs);

  friend bool operator==(const Pair& lhs, const Pair& rhs);

  friend bool operator!=(const Pair& lhs, const Pair& rhs);
};
static const Pair zero_pair = {0, 0};
static const Pair DOWN = {0, 1};
static const Pair UP = {0, -1};
static const Pair LEFT = {-1, 0};
static const Pair RIGHT = {1, 0};

#endif  // INCLUDE_MATHUTILS_PAIR_H_
