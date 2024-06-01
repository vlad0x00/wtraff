#include "led.hpp"
#include "print.hpp"

namespace wtraff {

LED::LED(const int pin)
  : pin(pin)
{
  pinMode(pin, OUTPUT);
  msg_println("LED created at pin ", pin);
}

[[nodiscard]] static uint8_t
make_power_uniform(const uint8_t power)
{
  // TODO: Write the function to make power transition uniform.
  return power;
}

void
LED::set_power(const uint8_t power)
{
  msg_println("Setting LED ", pin, " power to ", power);
  const auto power_raw = make_power_uniform(power);
  analogWrite(pin, power_raw);
}

} // namespace wtraff
