
ifndef RISCV
    $(error "Please make sure your RISCV environment variable is set.")
endif

export CC = $(RISCV)/bin/riscv64-unknown-elf-gcc
export LD = $(RISCV)/bin/riscv64-unknown-elf-ld
export AR = $(RISCV)/bin/riscv64-unknown-elf-ar
export OBJDUMP = $(RISCV)/bin/riscv64-unknown-elf-objdump

export CFLAGS += -march=rv32im -mabi=ilp32

export BUILD_DIR = $(shell pwd)/build
export BSP_LIB   = $(BUILD_DIR)/libzrbbsp.a

all: library examples

.PHONY: library
library:
	$(MAKE) -C ./libsrc

.PHONY: examples
examples: library
	$(MAKE) -C ./examples
