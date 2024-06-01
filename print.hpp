#ifndef WTRAFF_PRINT_HPP
#define WTRAFF_PRINT_HPP

#include "config.hpp"

#include <Arduino.h>

namespace wtraff {

[[nodiscard]] inline bool
init_print()
{
  if constexpr (PRINT_DEBUG) {
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial) {
    }
    Serial.print("Print initialized at baud rate ");
    Serial.println(SERIAL_BAUD_RATE);
  }
  return true;
}

template<typename... T>
inline void
msg_print(T... t)
{
  if constexpr (PRINT_DEBUG) {
    (Serial.print(t), ...);
    Serial.flush();
  }
}

template<typename... T>
inline void
msg_println(T... t)
{
  if constexpr (PRINT_DEBUG) {
    (Serial.print(t), ...);
    Serial.println();
    Serial.flush();
  }
}

} // namespace cvslpr

#endif
