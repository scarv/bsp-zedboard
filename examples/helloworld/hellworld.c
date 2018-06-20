
/*!
@file
@brief A very simple hello world example for the BSP
@details Implements a simple program which reads a string of upto 20
characters from the mailbox, and returns "Hello X!" where X is that string.
*/


#include "zrb_pkg.h"

#define RECV_BUF_LEN 20

static volatile uint8_t valid;  //! Set to non-zero when data is valid.
static volatile uint8_t ready;  //! Set to non-zero when data recieved.
static volatile uint8_t data;   //! The data to be transmitted.
static volatile uint8_t count;  //! Number of items left to transfer.

const char buffer [] = "Hello Zedboard!";
uint8_t    blen      = sizeof(buffer);

/*!
@brief Entry point for the program.
@details Jumped too from riscv_reset_handler in boot.S
*/
void riscv_main() {

    count = blen;

    while(1) {
        for(int i = 0; i < blen; i ++){
            while(valid) {
                // Do nothing, wait for reciever 
            }
            data = buffer[i];
            ready = 0;
            valid = 1;
            count --;
        }
    }
}


/*!
@brief Responsible for handling all interrupts.
@details Jumped too from riscv_irq_handler in boot.S
*/
void riscv_irq_delegated_handler() {
    // Do nothing.
    return;
}
