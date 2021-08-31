//
// Created by simakov on 15.08.2020.
//
#include <mathutils/random.h>

int get_seed(const int& init = 0, const int& top_limiter = 2004991) noexcept {
  static int counter = 0;

  using Nanoseconds = std::chrono::nanoseconds;
  using ClockType = std::chrono::system_clock;
  using TimeType = std::chrono::time_point<ClockType>;

  const TimeType timeStart = static_cast<TimeType>(Nanoseconds(init));
  const TimeType timeEnd = ClockType::now();

  int timeInterval = static_cast<int>(std::chrono::duration_cast<Nanoseconds>(timeEnd - timeStart).count());

  int seed = std::abs(timeInterval + counter) % top_limiter;

  counter += init + 1;

  if (counter > top_limiter) {
    counter -= top_limiter;
  }

  return seed;
}
