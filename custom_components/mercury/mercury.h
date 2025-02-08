#include "esphome.h"
#include <mercury.h>

class MercurySensor : public PollingComponent, public UARTDevice {
public:
  MercurySensor(UARTComponent *parent) : PollingComponent(15000), UARTDevice(parent) {}

  Mercury mercury = Mercury(16, 17, -1, -1, false, false);

  Sensor *total_consumption_sensor = new Sensor();
  Sensor *voltage_sensor = new Sensor();
  Sensor *current_sensor = new Sensor();
  Sensor *frequency_sensor = new Sensor();
  Sensor *temperature_sensor = new Sensor();

  void setup() override {
    mercury.begin(0, 9600, 150, 2);
    mercury.search();
    mercury.connect(1, "111111");
  }

  void update() override {
    float* total_consumption = mercury.energyTaF();
    float* voltage = mercury.voltage();
    float* current = mercury.current();
    float frequency = mercury.frequency();
    int temperature = mercury.temperature();

    total_consumption_sensor->publish_state(total_consumption[0]);
    voltage_sensor->publish_state(voltage[0]);
    current_sensor->publish_state(current[0]);
    frequency_sensor->publish_state(frequency);
    temperature_sensor->publish_state(temperature);
  }
};
