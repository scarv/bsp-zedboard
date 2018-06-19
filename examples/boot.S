
/*!
@file boot.S
@brief The basic boot script used to initialise the RISC-V core post reset.
*/

.section .text
.section .text.riscy_reset
riscy_reset_vector_landing:
    j riscy_reset_handler

.section .text.riscy_illegal_instr
riscy_illegal_instr_vector_landing:
    j riscy_illegal_instr_handler

.section .text.riscy_ecall
riscy_ecall_vector_landing:
    j riscy_ecall_handler

/* ------------------------------------------------------------*/

.section .text

//
// Whenever the core is reset, we end up here from riscy_reset_vector_landing
//
.global riscy_reset_handler
riscy_reset_handler:

    // Zero all of the registers
    mv  x1 , x0
    mv  x2 , x0
    mv  x3 , x0
    mv  x4 , x0
    mv  x5 , x0
    mv  x6 , x0
    mv  x7 , x0
    mv  x8 , x0
    mv  x9 , x0
    mv  x10, x0
    mv  x11, x0
    mv  x12, x0
    mv  x13, x0
    mv  x14, x0
    mv  x15, x0
    mv  x16, x0
    mv  x17, x0
    mv  x18, x0
    mv  x19, x0
    mv  x20, x0
    mv  x21, x0
    mv  x22, x0
    mv  x23, x0
    mv  x24, x0
    mv  x25, x0
    mv  x26, x0
    mv  x27, x0
    mv  x28, x0
    mv  x29, x0
    mv  x30, x0
    mv  x31, x0
    
    // Setup the stack pointer to the top of the shared memory.
    li  sp, 0xC0001FFC
    
    // Jump to main.
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

