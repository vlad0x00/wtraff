#include "timers.hpp"
#include "print.hpp"

#include <Arduino.h>

namespace wtraff {

bool
init_timers()
{
  // Set Timer1 (pins 9 and 10) to a faster PWM frequency
  TCCR1B = (TCCR1B & 0b11111000) | _BV(CS11);
  // Set Timer2 (pin 11) to a faster PWM frequency
  TCCR2B = (TCCR2B & 0b11111000) | _BV(CS21);

  msg_println("Timers prescaler set.");

  return true;
}

} // namespace wtraff
