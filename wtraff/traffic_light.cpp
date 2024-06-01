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
  while (bluetooth.available() < 2) {
  }

  const auto update_period1 = bluetooth.read();
  const auto update_period2 = bluetooth.read();

  const auto update_period = (update_period1 << 8) | update_period2;
  red_updater.set_update_period(update_period);
  yellow_updater.set_update_period(update_period);
  green_updater.set_update_period(update_period);

  msg_println(F("Set update period to "), update_period);
}

void
TrafficLight::work()
{
  if (bluetooth.available() >= 4) {
    const auto led = bluetooth.read();
    const auto end = bluetooth.read();

    const auto delta1 = bluetooth.read();
    const auto delta2 = bluetooth.read();
    // Combine deltas into a single value
    const auto delta = (static_cast<int16_t>(delta1) << 8) | delta2;

    msg_println(F("Received data. LED = "),
                led,
                F(", end = "),
                end,
                F(", delta = "),
                delta);

    switch (led) {
      case 0:
        red_updater.set_vals(end, delta);
        break;
      case 1:
        yellow_updater.set_vals(end, delta);
        break;
      case 2:
        green_updater.set_vals(end, delta);
        break;
    }
  }

  red_updater.update();
  yellow_updater.update();
  green_updater.update();
}

} // namespace wtraff
