#include "config.hpp"
#include "print.hpp"
#include "timers.hpp"
#include "traffic_light.hpp"

// Define the placement new operator
void*
operator new(const size_t size, void* const ptr)
{
  return ptr;
}

namespace wtraff {

uint8_t traffic_light_buf[sizeof(wtraff::TrafficLight)];
TrafficLight& traffic_light = *(wtraff::TrafficLight*)traffic_light_buf;

void
setup()
{
  init_print();
  if (!init_timers()) {
    msg_println("Failed to initialize timers.");
  }

  new (traffic_light_buf) TrafficLight(LED_RED_PIN,
                                       LED_YELLOW_PIN,
                                       LED_GREEN_PIN,
                                       BLUETOOTH_RX_PIN,
                                       BLUETOOTH_TX_PIN,
                                       BLUETOOTH_BAUD_RATE);
}

void
loop()
{
  traffic_light.work();
}

} // namespace wtrafft_timer_id;

void
setup()
{
  wtraff::setup();
}

void
loop()
{
  wtraff::loop();
}
