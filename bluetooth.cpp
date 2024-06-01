#include "bluetooth.hpp"
#include "print.hpp"

namespace wtraff {

Bluetooth::Bluetooth(const int rx_pin, const int tx_pin, const int baud_rate)
  : serial(tx_pin, rx_pin)
{
  serial.begin(baud_rate);
  msg_println("Bluetooth initialized at tx pin ",
              tx_pin,
              " and rx pin ",
              rx_pin,
              " at baud rate ",
              baud_rate);
}

void
Bluetooth::write(const uint8_t byte)
{
  serial.write(byte);
}

uint8_t
Bluetooth::read()
{
  return serial.read();
}

uint16_t
Bluetooth::available()
{
  return serial.available();
}

} // namespace wtraff
