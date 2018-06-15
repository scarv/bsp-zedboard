
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
    /* Base address of the shared BRAM */
    .text : { *(.riscy_main) } > PL_BRAM
    .text : { *(.text) } > PL_BRAM
    .data : { *(.data) } > PL_BRAM
    .bss  : { *(.bss ) } > PL_BRAM

    /* Don't include the .comment section anywhere */
    /DISCARD/ : { *(.comment) }
}

