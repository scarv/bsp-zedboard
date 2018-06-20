
/*!
@brief Implements the zrb_print function
*/

#include "zrb_print.h"


/*!
@details This function uses the shared UART core which is accessible to
both the PS and the PL of the Zedboard.
@note This function will *block* until the buffer is completely sent.
If the ARM core is also using the UART, the output will interleave, and
the resource contention will make everything much slower.
@warning It is *impossible* to distinguish whether some data came from the
zedboard or the ARM core without implementing your own resource sharing
protocol between the two.
*/
void zrb_print (
    const char * buffer,
    uint16_t     len
){

    // Enable transmit and recieve
    *ZRB_UART_CTRL = (0x1 << 4) |
                     (0x1 << 2) ;
    
    for(int i = 0; i < len; i ++) {
        while((*ZRB_UART_STATUS) & (0x1 << 4)) {
            // Do nothing, wait for the TX FIFO to empty.
        }
        // Writing to this register adds the new data to the send FIFO.
        *ZRB_UART_FIFO = buffer[i];
    }
}
