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

  void set_vals(uint8_t start, uint8_t end, int16_t delta);
  void update();

private:
  uint8_t current;
  uint8_t end;
  int16_t delta;

  T& object;
};

template<typename T, void (T::*METHOD)(uint8_t)>
inline void
Updater<T, METHOD>::set_vals(const uint8_t start,
                             const uint8_t end,
                             const int16_t delta)
{
  this->current = start;
  this->end = end;
  this->delta = delta;
}

template<typename T, void (T::*METHOD)(uint8_t)>
inline void
Updater<T, METHOD>::update()
{
  if (current != end) {
    (object.*METHOD)(current);

    const auto sum = current + delta;
    if (delta < 0 && sum <= end || delta > 0 && sum >= end) {
      current = end;
    } else {
      current = sum;
    }
  }
}

} // namespace wtraff

#endif // WTRAFF_UPDATER_HPP
