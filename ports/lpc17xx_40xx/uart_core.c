#include <unistd.h>
#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

#if MICROPY_MIN_USE_LPC1788_MCU

#include "board_api.h"

// Receive single character
int mp_hal_stdin_rx_chr(void)
{
    unsigned char c = 0;
#if MICROPY_MIN_USE_STDOUT
    int r = read(0, &c, 1);
    (void)r;
#elif MICROPY_MIN_USE_LPC1788_MCU
    c = Board_UARTGetChar();
#endif
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len)
{
#if MICROPY_MIN_USE_STDOUT
    int r = write(1, str, len);
    (void)r;
#elif MICROPY_MIN_USE_LPC1788_MCU
    while (len--)
    {
        Board_UARTPutChar(*str++);
    }
#endif
}

#endif
