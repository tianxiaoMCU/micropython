#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"

#include "chip.h"

#include "led.h"

STATIC mp_obj_t machine_reset(void)
{
    NVIC_SystemReset();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(machine_reset_obj, machine_reset);

STATIC mp_obj_t machine_freq(void)
{
    return mp_obj_new_int_from_uint(SystemCoreClock);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(machine_freq_obj, machine_freq);

STATIC const mp_rom_map_elem_t machine_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_machine)},

    {MP_ROM_QSTR(MP_QSTR_reset), MP_ROM_PTR(&machine_reset_obj)},
    {MP_ROM_QSTR(MP_QSTR_freq), MP_ROM_PTR(&machine_freq_obj)},

    {MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&pyb_led_type)},
};

STATIC MP_DEFINE_CONST_DICT(machine_module_globals, machine_module_globals_table);

const mp_obj_module_t machine_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&machine_module_globals,
};
