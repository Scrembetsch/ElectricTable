#include "app.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main()
{
    if (app_Init() != 0)
        return;

    while (1)
    {
        app_Loop(0.0f);

        vTaskDelay(100);
    }

    app_DeInit();
}