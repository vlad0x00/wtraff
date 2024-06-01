#ifndef WTRAFF_LED_HPP
#define WTRAFF_LED_HPP

#include <Arduino.h>

#include <stdint.h>

namespace wtraff {

class LED
{

public:
  explicit LED(int pin);

  // Power is from 0 to 255.
  void set_power(uint8_t power);

private:
  int pin;
};

} // namespace wtraff

#endif // WTRAFF_LED_HPP
