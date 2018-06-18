
/* Entry point / "main" function for the target program */
ENTRY(riscy_main)

/* Valid physical memory regions which can be used by the linker */
MEMORY {
    /* BRAM Shared between the ARM and RISCV cores.
       - Readable
       - Writable
       - Executable */
    PL_BRAM (wx) : ORIGIN = 0xC0000000, LENGTH = 8K
}

SECTIONS {
    /* Trampoline for getting to the reset handler */
    .text 0xC0000080 : { *(.text.riscy_reset) } > PL_BRAM

    /* Trampoline for getting to the illegal instruction handler */
    .text 0xC0000084 : { *(.text.riscy_illegal_instr) } > PL_BRAM

    /* Trampoline for getting to the environment call handler */
    .text 0xC0000088 : { *(.text.riscy_ecall) } > PL_BRAM

    /* The rest of the program code goes here */
    .text : { *(.text) } > PL_BRAM
    .data : { *(.data) } > PL_BRAM
    .bss  : { *(.bss ) } > PL_BRAM

    /* Don't include the .comment section anywhere */
    /DISCARD/ : { *(.comment) }
}

