#include "traffic_light.hpp"
#include "print.hpp"

namespace wtraff {

TrafficLight::TrafficLight(const int pin_red, const int pin_yellow, const int pin_green) 
  : red(pin_red)
  , yellow(pin_yellow)
  , green(pin_green)
  , red_updater(red)
  , yellow_updater(yellow)
  , green_updater(green)
{
  msg_println("TrafficLight created at pins ", pin_red, ", ", pin_yellow, ", ", pin_green);
}

} // namespace wtraff
