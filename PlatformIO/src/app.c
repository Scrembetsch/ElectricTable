#include "app.h"

#include "secret.h"

#include "lib_nvs.h"
#include "lib_wifi.h"

#include "esp_log.h"
#include "driver/gpio.h"

#define SWITCH_UP_PIN GPIO_NUM_12
#define SWITCH_DOWN_PIN GPIO_NUM_13

#define POWER_RELAY_PIN GPIO_NUM_21

// Motor Off -> Shirt Circuit if no protection is added and power is set to on
// High Side Off - Low Side Off -> Motor Off
// High Side Off - Low Side On  -> Counter-Clockwise
// High Side On  - Low Side Off -> Clockwise
// High Side On  - Low Side On  -> Motor Off
#define MOTOR_HIGH_SIDE_PIN GPIO_NUM_22
#define MOTOR_LOW_SIDE_PIN GPIO_NUM_23

int32_t app_Init()
{
    nvs_InitFlash();
    wifi_InitSoftAp(WIFI_SSID, WIFI_PASSWORD);

    gpio_set_direction(SWITCH_UP_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(SWITCH_DOWN_PIN, GPIO_MODE_INPUT);

    gpio_set_direction(POWER_RELAY_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_HIGH_SIDE_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_LOW_SIDE_PIN, GPIO_MODE_OUTPUT);

    return 0;
}

int state = 0;

void app_Loop(float dt)
{
}

void app_DeInit()
{
    nvs_DeInitFlash();
}

// Todo: Switching motor direction has to be handled with a time delay while the pwoer is turned off to avoid short circuits

void SetMotorDirection(MotorDirection direction)
{
    switch (direction)
    {
    case MOTOR_DIRECTION_OFF:
        gpio_set_level(POWER_RELAY_PIN, 0);
        gpio_set_level(MOTOR_HIGH_SIDE_PIN, 0);
        gpio_set_level(MOTOR_LOW_SIDE_PIN, 0);
        break;

    case MOTOR_DIRECTION_CLOCKWISE:
        gpio_set_level(POWER_RELAY_PIN, 1);
        gpio_set_level(MOTOR_HIGH_SIDE_PIN, 1);
        gpio_set_level(MOTOR_LOW_SIDE_PIN, 0);
        break;

    case MOTOR_DIRECTION_COUNTER_CLOCKWISE:
        gpio_set_level(POWER_RELAY_PIN, 1);
        gpio_set_level(MOTOR_HIGH_SIDE_PIN, 0);
        gpio_set_level(MOTOR_LOW_SIDE_PIN, 1);
        break;

    default:
        break;
    }
}