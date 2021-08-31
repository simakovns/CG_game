//
// Created by simakov on 15.08.2020.
//

#ifndef INCLUDE_MATHUTILS_RAND_H_
#define INCLUDE_MATHUTILS_RAND_H_

#include <mathutils/random.h>

#include <random>
class RandomCreator {
 public:
  RandomCreator() = default;

  int Get_random_int(const int& min, const int& max) {
    std::random_device rd;
    Spec_random::Random<> random_creator{rd()};
    return random_creator(min, max);
  }

  int Get_random_int(const int& min, const int& max, const int& seed) {
    Spec_random::Random<> random_creator{seed};
    return random_creator(min, max);
  }

  double Get_double_0_1() {
    std::random_device rd;
    Spec_random::Random<> random_creator{rd()};
    return random_creator();
  }
};

#endif  // INCLUDE_MATHUTILS_RAND_H_
