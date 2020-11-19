#include "esphome.h"
#include <Wire.h>
#include "Adafruit_MLX90614.h"

#define TAG "mlx90614"

class MLX90614Sensor : public PollingComponent {

  public:
    Adafruit_MLX90614 mlx;

    Sensor *ambient_temperature_sensor = new Sensor();
    Sensor *object_temperature_sensor = new Sensor();

    MLX90614Sensor() : PollingComponent(15000) { }

    void setup() override {
      ESP_LOGCONFIG(TAG, "Setting up MLX90614Sensor...");
      mlx.begin();
      LOG_SENSOR("  ", "Ambient temperature", this->ambient_temperature_sensor);
      LOG_SENSOR("  ", "Object temperature", this->object_temperature_sensor);
    }

    void update() override {
      double ambient_temperature = mlx.readAmbientTempC();
      double object_temperature = mlx.readObjectTempC();

      ESP_LOGD(TAG, "Ambient temperature measured: %f", ambient_temperature);
      ESP_LOGD(TAG, "Object temperature measured: %f", object_temperature);

      ambient_temperature_sensor->publish_state(ambient_temperature);
      object_temperature_sensor->publish_state(object_temperature);
    }
};
