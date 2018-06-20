
ifndef RISCV
    $(error "Please make sure your RISCV environment variable is set.")
endif

export CC = $(RISCV)/bin/riscv64-unknown-elf-gcc
export LD = $(RISCV)/bin/riscv64-unknown-elf-ld
export AR = $(RISCV)/bin/riscv64-unknown-elf-ar
export OBJDUMP = $(RISCV)/bin/riscv64-unknown-elf-objdump
export OBJCOPY = $(RISCV)/bin/riscv64-unknown-elf-objcopy

export CFLAGS += -march=rv32im -mabi=ilp32

export BUILD_DIR = $(shell pwd)/build
export BSP_LIB   = $(BUILD_DIR)/libzrbbsp.a

PORT    ?= /dev/ttyACM0
BINARY  ?= ./build/app_helloworld.bin

all: library examples

.PHONY: library
library:
	$(MAKE) -C ./libsrc

.PHONY: examples
examples: library
	$(MAKE) -C ./examples

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

upload: examples
	./tools/upload.py --port $(PORT) set-reset
	./tools/upload.py --port $(PORT) upload $(BINARY)
	./tools/upload.py --port $(PORT) clear-reset
	./tools/upload.py --port $(PORT) read-buffer


