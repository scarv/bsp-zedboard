
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
    .text 0xC0000000 : { *(.text.riscv_reset) } > PL_BRAM

    /* Trampoline for getting to the interrupt handler */
    .text 0xC0000010 : { *(.text.riscv_irq_handler) } > PL_BRAM

    /* The rest of the program code goes here */
    .text : { *(.text) } > PL_BRAM
    .data : { *(.data) } > PL_BRAM
    .bss  : { *(.bss ) } > PL_BRAM

    /* Don't include the .comment section anywhere */
    /DISCARD/ : { *(.comment) }
}

