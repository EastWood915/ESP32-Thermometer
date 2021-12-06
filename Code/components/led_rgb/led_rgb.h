#ifndef _LED_RGB_H_
#define _LED_RGB_H_

typedef enum led_rgb_color_t {
    LED_RGB_RED,
    LED_RGB_GREEN,
    LED_RGB_BLUE
} led_rgb_color_t;


void led_rgb_init(void);
void led_rgb_set(led_rgb_color_t color);


#endif //_LED_RGB_