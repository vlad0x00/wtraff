#include "traffic_light.hpp"
#include "print.hpp"

namespace wtraff {

TrafficLight::TrafficLight(const int pin_red,
                           const int pin_yellow,
                           const int pin_green,
                           const int bluetooth_rx_pin,
                           const int bluetooth_tx_pin,
                           const int bluetooth_baudrate)
  : red(pin_red)
  , yellow(pin_yellow)
  , green(pin_green)
  , red_updater(red)
  , yellow_updater(yellow)
  , green_updater(green)
  , bluetooth(bluetooth_rx_pin, bluetooth_tx_pin, bluetooth_baudrate)
{
}

void
TrafficLight::work()
{
  if (bluetooth.available() >= 5) {
    const auto led = bluetooth.read();
    const auto start = bluetooth.read();
    const auto end = bluetooth.read();

    const auto delta1 = bluetooth.read();
    const auto delta2 = bluetooth.read();
    // Combine deltas into a single value
    const auto delta = (static_cast<int16_t>(delta1) << 8) | delta2;

    switch (led) {
      case 'r':
        red_updater.set_vals(start, end, delta);
        break;
      case 'y':
        yellow_updater.set_vals(start, end, delta);
        break;
      case 'g':
        green_updater.set_vals(start, end, delta);
        break;
    }
  }

  red_updater.update();
  yellow_updater.update();
  green_updater.update();
}

} // namespace wtraff
