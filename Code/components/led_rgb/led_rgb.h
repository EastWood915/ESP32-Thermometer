#ifndef _LED_RGB_H_
#define _LED_RGB_H_

/*************  CONFIGURATION  *************/

#define LED_RGB_OUTPUT_RED         (21) // Define the output GPIO (red)
#define LED_RGB_OUTPUT_GREEN       (19) // Define the output GPIO (green)
#define LED_RGB_OUTPUT_BLUE        (18) // Define the output GPIO (blue)
#define LED_RGB_FREQUENCY          (2)  // Frequency in Hertz.

/*******  EXPORTED MACROS AND TYPES  *******/

#define LED_RGB_BLINK              (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LED_RGB_ON                 (8191) // Set duty to 100%
#define LED_RGB_OFF                (0)
typedef enum led_rgb_color_t {
    LED_RGB_RED,
    LED_RGB_GREEN,
    LED_RGB_BLUE,
    LED_RGB_YELLOW
} led_rgb_color_t;

/**********  EXPORTED FUNCTIONS  **********/

void led_rgb_init(void);
void led_rgb_set(led_rgb_color_t color, uint32_t mode);


#endif //_LED_RGB_