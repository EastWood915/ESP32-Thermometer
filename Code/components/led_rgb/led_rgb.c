#include <stdlib.h>
#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_err.h"
#include "led_rgb.h"

static const char *TAG = "led_rgb";

#define LED_RGB_TIMER              LEDC_TIMER_0
#define LED_RGB_MODE               LEDC_LOW_SPEED_MODE
#define LED_RGB_CHANNEL_RED        LEDC_CHANNEL_0
#define LED_RGB_CHANNEL_GREEN      LEDC_CHANNEL_1
#define LED_RGB_CHANNEL_BLUE       LEDC_CHANNEL_2
#define LED_RGB_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits

static ledc_timer_config_t ledc_timer = {
        .speed_mode       = LED_RGB_MODE,
        .timer_num        = LED_RGB_TIMER,
        .duty_resolution  = LED_RGB_DUTY_RES,
        .freq_hz          = LED_RGB_FREQUENCY, 
        .clk_cfg          = LEDC_AUTO_CLK
    };
static ledc_channel_config_t ledc_channel_red = {
        .speed_mode     = LED_RGB_MODE,
        .channel        = LED_RGB_CHANNEL_RED,
        .timer_sel      = LED_RGB_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_RGB_OUTPUT_RED,
        .duty           = LED_RGB_OFF, // Set duty to 0%
        .hpoint         = 0
    };
static ledc_channel_config_t ledc_channel_green = {
        .speed_mode     = LED_RGB_MODE,
        .channel        = LED_RGB_CHANNEL_GREEN,
        .timer_sel      = LED_RGB_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_RGB_OUTPUT_GREEN,
        .duty           = LED_RGB_OFF, // Set duty to 0%
        .hpoint         = 0
    };
static ledc_channel_config_t ledc_channel_blue = {
        .speed_mode     = LED_RGB_MODE,
        .channel        = LED_RGB_CHANNEL_BLUE,
        .timer_sel      = LED_RGB_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_RGB_OUTPUT_BLUE,
        .duty           = LED_RGB_OFF, // Set duty to 0%
        .hpoint         = 0
    };


void led_rgb_init(void)
{
    // Apply the LEDC PWM timer configuration
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Apply the LEDC PWM channel configuration
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_red));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_green));
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_blue));

    ESP_LOGI(TAG, "Initialized");
}

void led_rgb_set(led_rgb_color_t color, uint32_t mode)
{
    switch(color) 
    {
        case LED_RGB_RED:
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_RED, mode);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_GREEN, LED_RGB_OFF);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_BLUE, LED_RGB_OFF);
            ESP_LOGI(TAG, "Set to red");
            break;

        case LED_RGB_GREEN:
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_RED, LED_RGB_OFF);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_GREEN, mode);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_BLUE, LED_RGB_OFF);
            ESP_LOGI(TAG, "Set to green");
            break;

        case LED_RGB_BLUE:
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_RED, LED_RGB_OFF);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_GREEN, LED_RGB_OFF);
            ledc_set_duty(LED_RGB_MODE, LED_RGB_CHANNEL_BLUE, mode);
            ESP_LOGI(TAG, "Set to blue");
            break;
    }

    ledc_update_duty(LED_RGB_MODE, LED_RGB_CHANNEL_RED);
    ledc_update_duty(LED_RGB_MODE, LED_RGB_CHANNEL_GREEN);
    ledc_update_duty(LED_RGB_MODE, LED_RGB_CHANNEL_BLUE);
}