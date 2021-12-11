#include <stdio.h>
#include <string.h>
#include "ds18b20.h"
#include "dweet.h"
#include "led_rgb.h"
#include "button.h"
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

void task_button(void)
{
    while(1) 
    {
        button_main_function();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    led_rgb_init();
    led_rgb_set(LED_RGB_YELLOW, LED_RGB_ON);
    ESP_ERROR_CHECK(example_connect());
    ds18b20_init(15);
    button_init();
    xTaskCreate(&task_button, "TASK_BUTTON", 1024, NULL, 20, NULL);
    led_rgb_set(LED_RGB_GREEN, LED_RGB_ON);
    

    while(1)
    {
        temp = ds18b20_getTempC();
        (void)sprintf(stemp, "%.2f", temp);
        dweet_send("jbdhsuk", "temperature", stemp);

        if (BUTTON_PRESSED == button_get_state())
        {
            printf("Button pressed\n");
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
