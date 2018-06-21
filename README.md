
# Zedboard RISC-V Board Support Package

This repository contains a set of software tools and example applications
for working with RISC-V on the Zedboard development platform.

Note that this code is designed to work specifically with the subsystem
built as part of the SCARV project. This subsystem is not yet published,
but can be obtained by talking to [Ben Marshall](ben.marshall@bristol.ac.uk).

## Getting Started

1. Plug in the Zedboard UART/USB to the host PC. Wait for the *blue* LED to
   turn on.
2. Clone this repository. Move into it as the current working directory.
3. Set the `RISCV` environment variable, such that
   `$RISCV/bin/riscv64-unknown-elf-gcc` points to the right thing.
4. Check which port the Zedboard UART appears as under `/dev/tty*`. This
   is usually `/dev/ttyACM0`.
5. Run `make upload PORT=<your port>` to upload and run the HelloWorld
   example program.

## Useful links:

- [Picorv32 CPU Core](https://github.com/cliffordwolf/picorv32) - The
  RISC-V core implementation being used in the platform.
- [Zedboard platform](https://zedboard.org) - Zedboard homepage
  - [Zedboard Hardware User Manual](http://zedboard.org/sites/default/files/documentations/ZedBoard_HW_UG_v2_2.pdf) - Contains Zedboard specific details 
  for the Zynq SoC like how to boot it and where from.
  - [Zynq-7000 SoC Technical Reference Manual](https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf) - Contains complete
  peripheral listings for the Zynq memory mapped peripherals, including
  register descriptions for interfacing with them.

