
#ifndef ZRB_MAILBOX_H
#define ZRB_MAILBOX_H

#include "zrb_common.h"

//! Typedef representing a handle to a mailbox.
typedef volatile uint32_t * zrb_mailbox_t;

//
// Register indexes taken from page 12 of the Xilinx LogiCORE IP
// Mailbox Product Guide - (PG114).
static const uint8_t ZRB_MAILBOX_REG_WDATA  = 0x0;
static const uint8_t ZRB_MAILBOX_REG_RDATA  = 0x2;
static const uint8_t ZRB_MAILBOX_REG_STATUS = 0x4;
static const uint8_t ZRB_MAILBOX_REG_ERROR  = 0x5;
static const uint8_t ZRB_MAILBOX_REG_CTRL   = 0x11;

/*!
@brief Send a single 32 bit word to the supplied mailbox.
@param mb in - Handle to the mailbox to use.
@param to_send in - The data to send.
@returns void
*/
void zrb_mailbox_write (
    zrb_mailbox_t   mb,
    uint32_t        to_send
);


/*!
@brief Blocking read of a single 32 bit word from the supplied mailbox.
@param mb in - Handle to the mailbox to use.
@param recieved inout - The recieved word from the mailbox.
@note This function *blocks* until there is something inside the
mailbox to read. Don't use it if you do not expect to read something!
@returns void
*/
void zrb_mailbox_read (
    zrb_mailbox_t   mb,
    uint32_t       &recieved
);

/*!
@brief Non-blocking Read of a single 32 bit word from the supplied mailbox.
@param mb in - Handle to the mailbox to use.
@param recieved inout - The recieved word from the mailbox.
@note The value of the recieved parameter is unpredictable if the mailbox
was empty when this function was called.
*/
void zrb_mailbox_read_nb (
    zrb_mailbox_t   mb,
    uint32_t       &recieved
);



/*!
@brief Returns non-zero if the mailbox send buffer is full. Otherwise returns
zero.
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_send_buffer_full(
    zrb_mailbox_t   mb
);


/*!
@brief Returns non-zero if the mailbox recieve buffer is empty. Otherwise
returns zero.
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_recieve_buffer_empty(
    zrb_mailbox_t   mb
);


/*!
@brief Has there been a send error?
@details Returns non-zero if there have been attempts to send mail while the
mailbox send buffer is full. Otherwise returns zero.
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_send_buffer_full_error (
    zrb_mailbox_t   mb
);


/*!
@brief Has there been a recieve error?
@details Returns non-zero if there have been attempts to read mail while the
mailbox recieve buffer is empty. Otherwise returns zero.
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_recieve_buffer_empty_error (
    zrb_mailbox_t   mb
);


/*!
@brief Clear any send buffer full errors
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_clear_send_buffer_full_error (
    zrb_mailbox_t   mb
);


/*!
@brief Clear any recieve buffer empty errors
@param mb in - Handle to the mailbox to query.
*/
uint8_t zrb_mailbox_clear_recieve_buffer_empty_error (
    zrb_mailbox_t   mb
);

#endif

