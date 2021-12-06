#include <stdio.h>
#include <string.h>
#include "ds18b20.h"
#include "dweet.h"
#include "led_rgb.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "protocol_examples_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "esp_netif.h"
#include "esp_event.h"

float temp;
char stemp[8];

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());
    ds18b20_init(15);
    led_rgb_init();

    while(1)
    {
        temp = ds18b20_getTempC();
        (void)sprintf(stemp, "%.2f", temp);
        dweet_send("jbdhsuk", "temperature", stemp);

        led_rgb_set(LED_RGB_RED);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        led_rgb_set(LED_RGB_GREEN);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        led_rgb_set(LED_RGB_BLUE);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
