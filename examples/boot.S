
/*!
@file boot.S
@brief The basic boot script used to initialise the RISC-V core post reset.
*/

.section .text
.section .text.riscy_reset
riscy_reset_vector_landing:
    j   riscy_reset_handler


.section .text.riscy_illegal_instr
riscy_illegal_instr_vector_landing:
    j   riscy_illegal_instr_handler


.section .text.riscy_ecall
riscy_ecall_vector_landing:
    j   riscy_ecall_handler

/* ------------------------------------------------------------*/

.section .text

//
// Whenever the core is reset, we end up here from riscy_reset_vector_landing
//
.global riscy_reset_handler
riscy_reset_handler:
    j   riscy_main


//
// We land here after any illegal instruction
//
.global riscy_illegal_instr_handler
riscy_illegal_instr_handler:
    j   riscy_illegal_instr_delegated_handler


//
// We land here after any environment call
//
.global riscy_ecall_handler
riscy_ecall_handler:
    j   riscy_ecall_delegated_handler

