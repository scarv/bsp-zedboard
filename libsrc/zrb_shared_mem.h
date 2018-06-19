
/*!
@file
@brief Implements a very simple shared memory interface for sending
words between cores with a view into some shared memory.
*/

#ifndef ZRB_SHARED_MEM_H
#define ZRB_SHARED_MEM_H

#include "zrb_common.h"

//! A really simple struct for sharing letters between cores.
typedef struct {
    volatile uint8_t valid;  //! Set to non-zero when data is valid.
    volatile uint8_t ready;  //! Set to non-zero when data recieved.
    volatile uint8_t data;   //! The data to be transmitted.
    volatile uint8_t count;  //! Number of items left to transfer.
} zrb_shared_mem_char_t;


//! Blocking read of a single character.
void zrb_shared_mem_read_char (
    zrb_shared_mem_char_t * rx,     //!< The shared mem handle
    uint8_t               * recv    //!< Reference to receive data buffer.
);

//! Blocking write of a single character.
void zrb_shared_mem_write_char (
    zrb_shared_mem_char_t * rx,     //!< Shared mem handle
    uint8_t                 send    //!< Thing to send.
);


#endif

