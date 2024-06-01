#ifndef WTRAFF_BLUETOOTH_HPP
#define WTRAFF_BLUETOOTH_HPP

#include <SoftwareSerial.h>

#include <stdint.h>

namespace wtraff {

class Bluetooth {

public:

  Bluetooth(int rx_pin, int tx_pin, int baud_rate);

  void write(uint8_t byte);
  [[nodiscard]] uint8_t read();
  [[nodiscard]] uint16_t available();

private:

  SoftwareSerial serial;

};

} // namespace wtraff

#endif // WTRAFF_BLUETOOTH_HPP
