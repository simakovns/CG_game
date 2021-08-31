#ifndef INCLUDE_MATHUTILS_RANDOM_H_
#define INCLUDE_MATHUTILS_RANDOM_H_

#include <chrono>
#include <cmath>
#include <random>
#include <type_traits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Spec_random {  //  namespace Spec_random

template<typename Genrand = std::mt19937,
         typename Enable_if = std::enable_if_t<!std::is_same<Genrand, std::random_device>::value> >
class Random {
 public:
  constexpr Random() noexcept : Random<Genrand, Enable_if>::Random(Random<Genrand, Enable_if>::seed_default) {}
  constexpr Random(const Random<Genrand, Enable_if>&) noexcept = default;
  constexpr Random(Random<Genrand, Enable_if>&&) noexcept = default;
  constexpr Random(const int& seed) noexcept {
    this->m_genrand.seed(static_cast<typename Genrand::result_type>(seed));
  }

  ~Random() noexcept = default;

  constexpr Random<Genrand, Enable_if>& operator=(const Random<Genrand, Enable_if>&) noexcept = default;
  constexpr Random<Genrand, Enable_if>& operator=(Random<Genrand, Enable_if>&&) noexcept = default;

  constexpr void cooldown(const int& seed) noexcept {
    this->m_genrand.seed(static_cast<typename Genrand::result_type>(seed));
  }

  constexpr double operator()() noexcept {
    constexpr double temp_denominator = 1.0 / (static_cast<double>(Genrand::max() - Genrand::min()) + 1.0);
    return temp_denominator * static_cast<double>(m_genrand() - Genrand::min());
  }

  constexpr double operator()(const double& _begin, const double& _end) noexcept {
    return _begin + (_end - _begin) * (*this)();
  }
  constexpr int operator()(const int& _begin, const int& _end) noexcept {
    return _begin + static_cast<int>((_end - _begin) * (*this)());
  }

  constexpr double angle() noexcept {
    constexpr double angle_circle = 2 * M_PI;
    constexpr double temp_denominator = 1.0 / (static_cast<double>(Genrand::max() - Genrand::min()) + 1.0);
    return angle_circle * temp_denominator * static_cast<double>(m_genrand() - Genrand::min());
  }

 private:
  static constexpr const int seed_default = 0;
  Genrand m_genrand;
};

int get_seed(const int& init = 0, const int& top_limiter = 2004991) noexcept;

}  // namespace Spec_random

#endif  // INCLUDE_MATHUTILS_RANDOM_H_
