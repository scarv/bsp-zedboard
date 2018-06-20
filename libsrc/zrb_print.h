
/*!
@brief File declaring the interface to the simple zrb_print function.
*/

#ifndef ZRB_PRINT
#define ZRB_PRINT

#include "zrb_common.h"

/*!
@brief Print a character buffer to the UART line, bypassing the ARM core.
@param buffer in - The buffer to send.
@param len in - How much of the buffer to send.
@returns void
*/
void zrb_print (
    const char * buffer,
    uint16_t     len
);

#endif
