#include <stdlib.h>
#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_err.h"
#include "led_rgb.h"

static const char *TAG = "led_rgb";

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_RED         (21) // Define the output GPIO
#define LEDC_OUTPUT_GREEN       (19) // Define the output GPIO
#define LEDC_OUTPUT_BLUE        (18) // Define the output GPIO
#define LEDC_CHANNEL_RED        LEDC_CHANNEL_0
#define LEDC_CHANNEL_GREEN      LEDC_CHANNEL_1
#define LEDC_CHANNEL_BLUE       LEDC_CHANNEL_2
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_BLINK         (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_DUTY_ON            (8191)
#define LEDC_DUTY_OFF           (0)
#define LEDC_FREQUENCY          (2) // Frequency in Hertz. Set frequency at 5 kHz


void led_rgb_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY, 
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel_red = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_RED,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_RED,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ledc_channel_config_t ledc_channel_green = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_GREEN,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_GREEN,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ledc_channel_config_t ledc_channel_blue = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_BLUE,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_BLUE,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_red));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_green));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_blue));

    ESP_LOGI(TAG, "Initialized");
}

void led_rgb_set(led_rgb_color_t color)
{
    switch(color) 
    {
        case LED_RGB_RED:
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_RED, LEDC_DUTY_BLINK));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_GREEN, LEDC_DUTY_OFF));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_BLUE, LEDC_DUTY_OFF));

            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_RED));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_GREEN));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_BLUE));

            ESP_LOGI(TAG, "Set to red");

            break;

        case LED_RGB_GREEN:
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_RED, LEDC_DUTY_OFF));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_GREEN, LEDC_DUTY_BLINK));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_BLUE, LEDC_DUTY_OFF));

            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_RED));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_GREEN));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_BLUE));

            ESP_LOGI(TAG, "Set to green");

            break;

        case LED_RGB_BLUE:
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_RED, LEDC_DUTY_OFF));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_GREEN, LEDC_DUTY_OFF));
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_BLUE, LEDC_DUTY_BLINK));

            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_RED));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_GREEN));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_BLUE));

            ESP_LOGI(TAG, "Set to blue");

            break;
    }
}