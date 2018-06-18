
/*!
@file
@brief A very simple hello world example for the BSP
@details Implements a simple program which reads a string of upto 20
characters from the mailbox, and returns "Hello X!" where X is that string.
*/


#include "zrb_pkg.h"

#define RECV_BUF_LEN 20

/*!
@brief Send a character buffer through the mailbox send interface.
@param mailbox in - The mailbox to post the buffer into.
@param buf in - what to send.
@param len in - How much of buf to send.
@note This function will terminate early if it encounters a "\0" character
in buf.
*/
void send_buffer(
    zrb_mailbox_t   mailbox,
    char *          buf,
    uint32_t        len
) {
/*    for(int i = 0; i < len; i ++) {

        if(buf[i] == '\0') continue;
        
        while(zrb_mailbox_send_buffer_full(mailbox)) {
            // Wait...
        }

        uint32_t to_send = ((uint32_t)buf[i] & 0xFF);
        
        zrb_mailbox_write(mailbox, to_send);
    }*/
}

/*!
@brief Entry point for the program
@note This function must have it's program section set to ".riscy_main" so
that it appears first in the output binary we generate. Otherwise, the
program will start executing at some other random function.
*/
void riscy_main () {
    
    // Buffer for recieving data from the mailbox FIFO.
    //char recv_buf[RECV_BUF_LEN];

    //char resp_buf [] = "Hello ";

    //uint32_t recieved;
    
    // Handle to the mailbox FIFO
    zrb_mailbox_t mailbox = ZRB_RISCY_MAILBOX_BASE;

    uint32_t * ptr = (uint32_t*)0xC00000e0;

    // FIXME
    while(1) {
        zrb_mailbox_write(mailbox, (uint32_t)"abcd");
        *ptr = (*ptr) + 1;
    }
/*
    // Start with a "Hello World!";
    char helloworld [] = "Hello World!";
    send_buffer(mailbox, helloworld, sizeof(helloworld));

    // Loop forever...
    while(1) {

        // Recieve some string from the mailbox.
        for(int i = 0; i < RECV_BUF_LEN; i ++) {
            
            // Read from the mailbox using the blocking read function.
            zrb_mailbox_read(mailbox, &recieved);
            
            // Mask the recieved word into a single char.
            recv_buf [i] = (char)(recieved & 0xFF);

            if(recv_buf[i] == '\0') {
                // End of the recieved string.
                continue;
            }

        }
        
        // Send the generic "hello"
        send_buffer(mailbox, resp_buf, RECV_BUF_LEN);

        // Make our greeting personal...
        send_buffer(mailbox, recv_buf, RECV_BUF_LEN);
    }
*/
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
