#include <esp_log.h>
#include <esp_wifi_types_generic.h>
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp-now_protocol.h>
#include <temperature_sensor.h>
#include <esp_now.h>

#define TEMPERATURE_PIN GPIO_NUM_4

#define delay(x) vTaskDelay((x) / portTICK_PERIOD_MS)

static const char *TAG = "MAIN";


void app_main(void)
{
    esp_now_initialization();
    temperature_init(TEMPERATURE_PIN);

    uint8_t broadcast_addr[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, broadcast_addr, 6);
    peer.channel = 0;
    peer.encrypt = false;

    ESP_ERROR_CHECK(esp_now_add_peer(&peer));

    const char msg[] = "hello_from_sensor";

    int16_t temperature, humidity;
    while(1) {
        temperature_get_data(&temperature, &humidity);
        esp_now_send(broadcast_addr, (uint8_t*)msg, sizeof(msg));
        ESP_LOGI(TAG, "Sent message");
        delay(3000);
    }
}
