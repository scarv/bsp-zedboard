
/*!
@file
@brief A very simple hello world example for the BSP
@details Implements a simple program which reads a string of upto 20
characters from the mailbox, and returns "Hello X!" where X is that string.
*/


#include "zrb_pkg.h"

#define RECV_BUF_LEN 20

const char buffer2[] = "Hello World!\n";
uint16_t   blen2     = sizeof(buffer2);

/*!
@brief Entry point for the program.
@details Jumped too from riscv_reset_handler in boot.S
*/
void riscv_main() {

    uint32_t * gpio = (uint32_t*)0x20001000;
    *gpio = 0xF;

    for(int i = 0; i < 10; i ++) {
        zrb_print(buffer2,blen2);
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
