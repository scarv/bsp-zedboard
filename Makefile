
ifndef RISCV
    $(error "Please make sure your RISCV environment variable is set.")
endif

export CC = $(RISCV)/bin/riscv64-unknown-elf-gcc
export LD = $(RISCV)/bin/riscv64-unknown-elf-ld
export AR = $(RISCV)/bin/riscv64-unknown-elf-ar

all: library

library:
	$(MAKE) -C ./libsrc
