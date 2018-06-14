
#include "zrb_mailbox.h"


/*!
*/
void zrb_mailbox_write (
    zrb_mailbox_t   mb,
    uint32_t        to_send
){
    mb[ZRB_MAILBOX_REG_WDATA] = to_send;
}


/*!
*/
void zrb_mailbox_read (
    zrb_mailbox_t   mb,
    uint32_t       *recieved
){
    while(zrb_mailbox_recieve_buffer_empty(mb)) {
        // Do nothing.
    }
    *recieved = mb[ZRB_MAILBOX_REG_RDATA];
}

/*!
*/
void zrb_mailbox_read_nb (
    zrb_mailbox_t   mb,
    uint32_t       *recieved
){
    *recieved = mb[ZRB_MAILBOX_REG_RDATA];
}



/*!
*/
uint8_t zrb_mailbox_send_buffer_full(
    zrb_mailbox_t   mb
){
    return mb[ZRB_MAILBOX_REG_STATUS] & 0x2;
}


/*!
*/
uint8_t zrb_mailbox_recieve_buffer_empty(
    zrb_mailbox_t   mb
){
    return mb[ZRB_MAILBOX_REG_STATUS] & 0x1;
}


/*!
*/
uint8_t zrb_mailbox_send_buffer_full_error (
    zrb_mailbox_t   mb
){
    return mb[ZRB_MAILBOX_REG_ERROR] & 0x2;
}


/*!
*/
uint8_t zrb_mailbox_recieve_buffer_empty_error (
    zrb_mailbox_t   mb
){
    return mb[ZRB_MAILBOX_REG_ERROR] & 0x1;
}


/*!
*/
uint8_t zrb_mailbox_clear_send_buffer_full_error (
    zrb_mailbox_t   mb
){
    mb[ZRB_MAILBOX_REG_ERROR] &= ~0x2;
}


/*!
*/
uint8_t zrb_mailbox_clear_recieve_buffer_empty_error (
    zrb_mailbox_t   mb
){
    mb[ZRB_MAILBOX_REG_ERROR] &= ~0x1;
}

