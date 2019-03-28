#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"

#include "chip.h"
#include "board.h"
#include "led.h"

/// \moduleref pyb
/// \class LED - LED object
///
/// The LED object controls an individual LED (Light Emitting Diode).
typedef struct _pyb_led_obj_t
{
    mp_obj_base_t base;
    mp_uint_t led_id;
} pyb_led_obj_t;

STATIC const pyb_led_obj_t pyb_led_obj[] = {
    {{&pyb_led_type}, PYB_LED_TOP_LEFT_1},
    {{&pyb_led_type}, PYB_LED_TOP_RIGHT_1},
    {{&pyb_led_type}, PYB_LED_TOP_RIGHT_2},
    {{&pyb_led_type}, PYB_LED_TOP_LEFT_2},
};
#define NUM_LEDS MP_ARRAY_SIZE(pyb_led_obj)

/******************************************************************************/
/* MicroPython bindings                                                       */

void led_obj_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "LED(%u)", self->led_id);
}

/// \classmethod \constructor(id)
/// Create an LED object associated with the given LED:
///
///   - `id` is the LED number, 1-4.
STATIC mp_obj_t led_obj_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, 1, false);

    // get led number
    mp_int_t led_id = mp_obj_get_int(args[0]);

    // check led number
    if (!(1 <= led_id && led_id <= NUM_LEDS))
    {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "LED(%d) doesn't exist", led_id));
    }

    // return static led object
    return MP_OBJ_FROM_PTR(&pyb_led_obj[led_id - 1]);
}

/// \method on()
/// Turn the LED on.
mp_obj_t led_obj_on(mp_obj_t self_in)
{
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    Board_LED_Set(self->led_id, true);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(led_obj_on_obj, led_obj_on);

/// \method off()
/// Turn the LED off.
mp_obj_t led_obj_off(mp_obj_t self_in)
{
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    Board_LED_Set(self->led_id, false);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(led_obj_off_obj, led_obj_off);

/// \method toggle()
/// Toggle the LED between on and off.
mp_obj_t led_obj_toggle(mp_obj_t self_in)
{
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    Board_LED_Toggle(self->led_id);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(led_obj_toggle_obj, led_obj_toggle);

STATIC const mp_rom_map_elem_t led_locals_dict_table[] = {
    // instance methods
    {MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&led_obj_on_obj)},
    {MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&led_obj_off_obj)},
    {MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&led_obj_toggle_obj)},

    // class constants
    {MP_ROM_QSTR(MP_QSTR_TOP_LEFT_1), MP_ROM_INT(PYB_LED_TOP_LEFT_1)},
    {MP_ROM_QSTR(MP_QSTR_TOP_RIGHT_1), MP_ROM_INT(PYB_LED_TOP_RIGHT_1)},
    {MP_ROM_QSTR(MP_QSTR_TOP_RIGHT_2), MP_ROM_INT(PYB_LED_TOP_RIGHT_2)},
    {MP_ROM_QSTR(MP_QSTR_TOP_LEFT_2), MP_ROM_INT(PYB_LED_TOP_LEFT_2)},
};

STATIC MP_DEFINE_CONST_DICT(led_locals_dict, led_locals_dict_table);

const mp_obj_type_t pyb_led_type = {
    {&mp_type_type},
    .name = MP_QSTR_LED,
    .print = led_obj_print,
    .make_new = led_obj_make_new,
    .locals_dict = (mp_obj_dict_t *)&led_locals_dict,
};
