#ifndef _BUTTON_H_
#define _BUTTON_H_

/*************  CONFIGURATION  *************/

#define BUTTON_PIN            (5u)
#define BUTTON_FILTER_PERIOD  (3u)

/*******  EXPORTED MACROS AND TYPES  *******/

#define BUTTON_STATE_ACTIVE   (0u)
#define BUTTON_STATE_INACTIVE (1u)

typedef enum button_state_t{
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_AND_READ
}button_state_t;

/**********  EXPORTED FUNCTIONS  **********/

void button_init(void);
void button_main_function(void);
button_state_t button_get_state(void);


#endif //_BUTTON_H_