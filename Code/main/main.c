#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20.h"



void app_main(void)
{
    ds18b20_init(15);
 
    while(1)
    {
        float temp = ds18b20_getTempC();
        printf("Temperatura: %dC\n", (int)temp);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
