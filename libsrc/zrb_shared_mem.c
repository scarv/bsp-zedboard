
#include "zrb_shared_mem.h"


//! Blocking read of a single character
void zrb_shared_mem_read_char (
    zrb_shared_mem_char_t * rx,     //!< The shared mem handle
    uint8_t               * recv    //!< Reference to receive data buffer.
){
    while(!rx -> valid) {
        // Do nothing, wait for transmitter
    }
    *recv = rx -> data;
    rx -> ready = 1;
    rx -> valid = 0;
}


void zrb_shared_mem_write_char (
    zrb_shared_mem_char_t * tx,     //!< Shared mem handle
    uint8_t                 send    //!< Thing to send.
){
    while(tx -> valid) {
        // Do nothing, wait for reciever 
    }
    tx -> data = send;
    tx -> ready = 0;
    tx -> valid = 1;
}
