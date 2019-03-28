#ifndef MICROPY_INCLUDED_LPC1788_MODULES_LED_H
#define MICROPY_INCLUDED_LPC1788_MODULES_LED_H

typedef enum
{
    PYB_LED_TOP_LEFT_1 = 1,
    PYB_LED_TOP_RIGHT_1 = 2,
    PYB_LED_TOP_RIGHT_2 = 3,
    PYB_LED_TOP_LEFT_2 = 4,
} pyb_led_t;

extern const mp_obj_type_t pyb_led_type;

#endif // MICROPY_INCLUDED_LPC1788_MODULES_LED_H
