
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

const char buffer [] = "Hello World!";
uint8_t    blen      = sizeof(buffer);

/*!
@brief Entry point for the program
@note This function must have it's program section set to ".riscy_main" so
that it appears first in the output binary we generate. Otherwise, the
program will start executing at some other random function.
*/
void riscy_main () {

    while(1) {

        count = blen;

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
