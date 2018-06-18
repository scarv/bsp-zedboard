
/*!
@file zrb_default_handlers.h
@brief Contains declarations for the reset, environment call and
illegal instruction handlers.
*/

#include "zrb_common.h"


/*!
@brief The main function, called post reset.
*/
void riscy_main ();


/*!
@brief Handles all illegal instruction exceptions.
*/
void riscy_illegal_instr_delegated_handler ();


/*!
@brief Handles environment (sycall) exceptions.
*/
void riscy_ecall_delegated_handler ();

