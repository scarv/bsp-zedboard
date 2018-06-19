
/*!
@file
@brief A very simple hello world example for the BSP
@details Implements a simple program which reads a string of upto 20
characters from the mailbox, and returns "Hello X!" where X is that string.
*/


#include "zrb_pkg.h"

#define RECV_BUF_LEN 20

static volatile uint32_t       sword;
static zrb_shared_mem_char_t   schar;

/*!
@brief Entry point for the program
@note This function must have it's program section set to ".riscy_main" so
that it appears first in the output binary we generate. Otherwise, the
program will start executing at some other random function.
*/
void riscy_main () {

    const char buffer [] = "Hello World!";
    uint8_t    blen      = sizeof(buffer);

    for(int i = 0; i < 0x8000000; i ++) {
        sword = sword ^ (sword + 1);
        zrb_shared_mem_write_char(&schar, buffer[i%blen]);
    }
}


/*!
@brief Handles all illegal instruction exceptions.
*/
void riscy_illegal_instr_delegated_handler () {
    // Do nothing.
    return;
}


/*!
@brief Handles environment (sycall) exceptions.
*/
void riscy_ecall_delegated_handler () {
    // Do nothing.
    return;
}
