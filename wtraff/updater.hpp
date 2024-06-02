#ifndef WTRAFF_UPDATER_HPP
#define WTRAFF_UPDATER_HPP

#include <math.h>
#include <stdint.h>

namespace wtraff {

template<typename T, void (T::*METHOD)(uint8_t)>
class Updater
{

public:
  explicit Updater(T& object)
    : object(object)
  {
  }

  void set_vals(uint8_t end, int16_t delta);
  void set_update_period(const uint16_t period) { update_period = period; }
  void update();

private:
  uint8_t current = 0;
  uint8_t end = 0;
  int16_t delta = 0;
  uint16_t update_counter = 0;
  uint16_t update_period = 10;

  T& object;
};

template<typename T, void (T::*METHOD)(uint8_t)>
inline void
Updater<T, METHOD>::set_vals(const uint8_t end, const int16_t delta)
{
  this->end = end;
  this->delta = delta;
}

template<typename T, void (T::*METHOD)(uint8_t)>
inline void
Updater<T, METHOD>::update()
{
  (object.*METHOD)(current);
  if (current != end) {
    if (update_counter % update_period == 0) {
      const auto sum = current + delta;
      if (delta < 0 && sum <= end || delta > 0 && sum >= end) {
        current = end;
      } else {
        current = sum;
      }
    }
  } else if (end > 0) {
    end = 0;
    delta = static_cast<int16_t>(-1.5 * delta);
  }
  update_counter += 1;
}

} // namespace wtraff

#endif // WTRAFF_UPDATER_HPP
