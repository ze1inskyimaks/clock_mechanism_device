#include "temperature_sensor.h"

#include <esp_log.h>

#include "dht.h"

static gpio_num_t dht_pin = -1;

static const char *TAG = "temperature_sensor";

esp_err_t temperature_init(gpio_num_t pin) {
    ESP_LOGV(TAG,"Temperature sensor init with pin: %d, new init data: %d", dht_pin, pin);

    if (dht_pin == pin)
        return ESP_OK;
    dht_pin = pin;
    gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
    return ESP_OK;
}

esp_err_t temperature_get_data(int16_t *temperature, int16_t *humidity) {
    if(dht_pin == -1)
        return ESP_FAIL;

    if (temperature == NULL || humidity == NULL)
        return ESP_ERR_INVALID_ARG;


    if (dht_read_data(SENSOR_TYPE, dht_pin, humidity, temperature) == ESP_OK)
        return ESP_OK;

    return ESP_FAIL;
}