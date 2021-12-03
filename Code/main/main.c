#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20.h"

void app_main(void)
{
    ds18b20_init(15);
    while(1)
    {
        printf("Hello World!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
