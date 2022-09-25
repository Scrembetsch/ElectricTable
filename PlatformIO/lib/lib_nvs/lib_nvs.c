#include "lib_nvs.h"

#include "nvs_flash.h"

void nvs_InitFlash()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void nvs_DeInitFlash()
{
    ESP_ERROR_CHECK(nvs_flash_deinit());
}