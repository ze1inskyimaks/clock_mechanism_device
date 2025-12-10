//
// Created by autoh on 10.12.2025.
//

#ifndef CLOCK_MECHANISM_DEVICE_TEMPERATURE_SENSOR_H
#define CLOCK_MECHANISM_DEVICE_TEMPERATURE_SENSOR_H

#define SENSOR_TYPE DHT_TYPE_DHT11

#include "esp_err.h"
#include "soc/gpio_num.h"

esp_err_t temperature_init(gpio_num_t pin);

esp_err_t temperature_get_data(int16_t *temperature, int16_t *humidity);

#endif //CLOCK_MECHANISM_DEVICE_TEMPERATURE_SENSOR_H