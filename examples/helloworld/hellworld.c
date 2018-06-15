
/*!
@file
@brief A very simple hello world example for the BSP
@details Implements a simple program which reads a string of upto 20
characters from the mailbox, and returns "Hello X!" where X is that string.
*/


#include "zrb_pkg.h"

#define RECV_BUF_LEN 20


/*!
@brief Entry point for the program
*/
void riscy_main () {
    
    // Buffer for recieving data from the mailbox FIFO.
    char recv_buf[RECV_BUF_LEN];

    char resp_buf [] = "Hello ";

    uint32_t recieved;
    
    // Handle to the mailbox FIFO
    zrb_mailbox_t mailbox = ZRB_RISCY_MAILBOX_BASE;

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
        

        // Say hello.
        for(int i = 0; i < sizeof(resp_buf); i ++) {

            if(resp_buf[i] == '\0') continue;
            
            while(zrb_mailbox_send_buffer_full(mailbox)) {
                // Wait...
            }

            uint32_t to_send = ((uint32_t)resp_buf[i] & 0xFF);
            
            zrb_mailbox_write(mailbox, to_send);
        }

        // Make our greeting personal...
        for(int i = 0; i < RECV_BUF_LEN; i ++) {
            
            if(recv_buf[i] == '\0') continue;
            
            while(zrb_mailbox_send_buffer_full(mailbox)) {
                // Wait...
            }

            uint32_t to_send = ((uint32_t)recv_buf[i] & 0xFF);
            
            zrb_mailbox_write(mailbox, to_send);

        }
    }
}
