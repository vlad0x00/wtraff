#include "bluetooth.hpp"
#include "traffic_light.hpp"
#include "config.hpp"
#include "print.hpp"

void setup() {
  wtraff::init_print();
  wtraff::Bluetooth bluetooth(wtraff::BLUETOOTH_RX_PIN, wtraff::BLUETOOTH_TX_PIN, wtraff::BLUETOOTH_BAUD_RATE);
}

void loop() {
  //if (bluetooth.available()) {
  //  const auto b = bluetooth.read();
  //  Serial.write(b);
  //}

  // Check if data is available from the serial monitor
  //if (Serial.available()) {
  //  const auto b = Serial.read();
  //  bluetooth.write(b); // Send the received data to HC-06
 // }
}
