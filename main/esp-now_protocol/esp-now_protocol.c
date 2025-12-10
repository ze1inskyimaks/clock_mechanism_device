#include <nvs_flash.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"

static const char *TAG = "SENDER";

esp_err_t wifi_init();
void send_cb(const wifi_tx_info_t *info, esp_now_send_status_t status);

esp_err_t esp_now_initialization()
{
    ESP_ERROR_CHECK(wifi_init());

    ESP_ERROR_CHECK(esp_now_init());

    esp_now_register_send_cb(send_cb);

    return ESP_OK;
}

esp_err_t wifi_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    return ESP_OK;
}

void send_cb(const wifi_tx_info_t *info, esp_now_send_status_t status)
{
    const uint8_t *mac = info->des_addr;

    ESP_LOGI("ESPNOW", "SEND to: %02X:%02X:%02X:%02X:%02X:%02X  status=%d",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
             status);
}