#ifndef WTRAFF_TRAFFIC_LIGHT_HPP
#define WTRAFF_TRAFFIC_LIGHT_HPP

#include "led.hpp"
#include "updater.hpp"
#include "bluetooth.hpp"

#include <stdint.h>

namespace wtraff {

class TrafficLight {

public:

  TrafficLight(int pin_red, int pin_yellow, int pin_green);

  void work();

private:

  LED red;
  LED yellow;
  LED green;

  Updater<LED, &LED::set_power> red_updater;
  Updater<LED, &LED::set_power> yellow_updater;
  Updater<LED, &LED::set_power> green_updater;

};

} // namespace wtraff

#endif // WTRAFF_TRAFFIC_LIGHT_HPP
