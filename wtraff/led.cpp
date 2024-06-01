#include "led.hpp"
#include "print.hpp"

#include <math.h>

namespace wtraff {

LED::LED(const int pin)
  : pin(pin)
{
  pinMode(pin, OUTPUT);
  msg_println(F("LED created at pin "), pin);
}

[[nodiscard]] static uint8_t
make_power_uniform(const uint8_t power)
{
  static constexpr int MIN = 5;
  static constexpr int MAX = 255;
  static constexpr int STEPS[] = { 10, 20, 30, 40 };

  // Normalize the input to the range 0-1
  const auto normalized = static_cast<double>(power) / 255.0;

  // Apply a quadratic transformation to create a non-uniform mapping
  const auto transformed = pow(normalized, 1.5);

  // Map the transformed input to the desired range 20-255
  const auto output = static_cast<uint8_t>(MIN + transformed * (MAX - MIN));

  return output;
}

void
LED::set_power(const uint8_t power)
{
  const auto power_raw = make_power_uniform(power);
  msg_println(F("Setting LED "),
              pin,
              F(" power to "),
              power,
              F(", power raw = "),
              power_raw);
  analogWrite(pin, power_raw);
}

} // namespace wtraff
