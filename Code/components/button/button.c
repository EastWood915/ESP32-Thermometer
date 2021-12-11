#include "button.h"
#include "driver/gpio.h"

static button_state_t button_state;

void button_init()
{
    gpio_config_t cfg = {};
    cfg.pin_bit_mask = 1ull << BUTTON_PIN;
    cfg.mode = GPIO_MODE_INPUT;
    cfg.pull_up_en = 0;
    cfg.pull_down_en = 0;
    cfg.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&cfg);
    button_state = BUTTON_RELEASED;
}

button_state_t button_get_state()
{
    button_state_t state = button_state;

    /* Change state machine state after readout */
    if (button_state == BUTTON_PRESSED) button_state = BUTTON_PRESSED_AND_READ;
    return state;
}

void button_main_function()
{
    static uint8_t button_debounce_counter = 0;
    int state = gpio_get_level(BUTTON_PIN);

    switch (button_state)
    {
        case BUTTON_RELEASED:
            
            if (BUTTON_STATE_ACTIVE == state) button_debounce_counter++;
            else button_debounce_counter = 0;

            if(button_debounce_counter > BUTTON_FILTER_PERIOD)
            {
                button_debounce_counter = 0;
                button_state = BUTTON_PRESSED;
            } 
            break;

        case BUTTON_PRESSED:

            /* No action, waiting for button_get_state() call */
            break;

        case BUTTON_PRESSED_AND_READ:

            if (BUTTON_STATE_INACTIVE == state) button_debounce_counter++;
            else button_debounce_counter = 0;

            if(button_debounce_counter > BUTTON_FILTER_PERIOD)
            {
                button_debounce_counter = 0;
                button_state = BUTTON_RELEASED;
            } 

            break;

        default:

            button_state = BUTTON_RELEASED;
            break;
    }
}