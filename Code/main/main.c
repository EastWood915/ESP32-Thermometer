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
#include "esp_log.h"

typedef enum 
{
    STATE_MACHINE_INIT = 0x00,
    STATE_MACHINE_FAULT_CON = 0xA5,
    STATE_MACHINE_FAULT_SENSOR = 0x5A,
    STATE_MACHINE_WPS = 0x69,
    STATE_MACHINE_MAIN = 0x96
}StateMachine_State_t;

float temp;
char stemp[8];

void task_button(void * pvParameters)
{
    while(1) 
    {
        button_main_function();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void task_main(void * pvParameters)
{
    static StateMachine_State_t state_machine_state = STATE_MACHINE_INIT;
    static float temp;
    static float temp_filtered = 0;
    static char stemp[8];
    static int fault_ctr = 0;
    static int loop_ctr = 0;

    while(1)
    {
        ESP_LOGI("task_main", "state = %X", state_machine_state);
        switch(state_machine_state)
        {
            case STATE_MACHINE_INIT:

                /* Try to connect to network */
                if(ESP_OK != example_connect())
                {
                    led_rgb_set(LED_RGB_RED, LED_RGB_BLINK);
                    state_machine_state = STATE_MACHINE_FAULT_CON;
                    break;
                }

                /* Check if sensor works */
                temp = ds18b20_getTempC();
                if((temp < 0) || (temp > 100))
                {
                    led_rgb_set(LED_RGB_RED, LED_RGB_ON);
                    state_machine_state = STATE_MACHINE_FAULT_SENSOR;
                    break;
                }

                /* Lookin good! Go to the main state */
                led_rgb_set(LED_RGB_GREEN, LED_RGB_ON);
                state_machine_state = STATE_MACHINE_MAIN;
                break;

            case STATE_MACHINE_MAIN:

                /* Get measurement and validate it*/
                temp = ds18b20_getTempC();
                if((temp < 0) || (temp > 100))
                {
                    fault_ctr++;
                }
                else 
                {
                    temp_filtered = temp;
                    fault_ctr = 0;
                }

                /* Increment loop counter */
                loop_ctr++;

                /* If proper time elapsed, send data */
                if (10 <= loop_ctr)
                {
                    (void)sprintf(stemp, "%.2f", temp_filtered);
                    dweet_send("jbdhsuk", "temperature", stemp);
                    loop_ctr = 0;
                }

                /* Chech if WPS is requested */
                if (BUTTON_PRESSED == button_get_state())
                {
                    state_machine_state = STATE_MACHINE_WPS;
                }

                /* Check for failures */
                if (5 <= fault_ctr) 
                {
                    led_rgb_set(LED_RGB_RED, LED_RGB_ON);
                    state_machine_state = STATE_MACHINE_FAULT_SENSOR;
                    break;
                }
                
                break;

            case STATE_MACHINE_WPS:
                led_rgb_set(LED_RGB_BLUE, LED_RGB_ON);
                break;

            case STATE_MACHINE_FAULT_SENSOR:

                /* Check if sensor started working */
                if((temp > 0) && (temp < 100))
                {
                    led_rgb_set(LED_RGB_GREEN, LED_RGB_ON);
                    state_machine_state = STATE_MACHINE_MAIN;
                }
                break;

            case STATE_MACHINE_FAULT_CON:

                /* Try to reconnect */
                if(ESP_OK == example_connect())
                {
                    led_rgb_set(LED_RGB_GREEN, LED_RGB_ON);
                    state_machine_state = STATE_MACHINE_MAIN;
                }
                break;

            default:

                esp_restart();
                break;
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task_init(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    led_rgb_init();
    led_rgb_set(LED_RGB_YELLOW, LED_RGB_ON);
    ds18b20_init(15);
    button_init();
    xTaskCreate(&task_button, "TASK_BUTTON", 1024, NULL, 20, NULL);
    xTaskCreate(&task_main, "TASK_MAIN", 4096, NULL, 10, NULL);
}

void app_main(void)
{
    task_init();
}
