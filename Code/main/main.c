#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20.h"

DeviceAddress tempSensor = {0};

void app_main(void)
{
    printf("Address 0: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", tempSensor[0],tempSensor[1],tempSensor[2],tempSensor[3],tempSensor[4],tempSensor[5],tempSensor[6],tempSensor[7]);
    ds18b20_init(15);
    ds18b20_search(tempSensor,true);
    //ds18b20_setResolution(&tempSensor,2,10);
    printf("Address 0: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", tempSensor[0],tempSensor[1],tempSensor[2],tempSensor[3],tempSensor[4],tempSensor[5],tempSensor[6],tempSensor[7]);

    while(1)
    {
        ds18b20_requestTemperatures();
        float temp = ds18b20_getTempC((DeviceAddress *)&tempSensor);
        printf("Hello World! %f\n", temp);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
