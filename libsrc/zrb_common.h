
/*!
@file zrb_common.h
@brief Contains all of the boring constant and type definitions used by the
BSP.
*/

#ifndef ZRB_COMMON_H
#define ZRB_COMMON_H

#include "stdint.h"

//! Base address of the mailbox used to communicate with the ARM core.
static volatile uint32_t * ZRB_MAILBOX_BASE  = (uint32_t*)0x20000000;

//! Base address of the BRAM memory shared with the ARM core.
static volatile uint32_t * ZRB_BRAM_BASE     = (uint32_t*)0xC0000000;

//! Size of the BRAM memory shared with the ARM core.
static volatile uint32_t   ZRB_BRAM_SIZE     = 0x00007FFF;

#endif

