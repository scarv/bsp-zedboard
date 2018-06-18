
BUILD_DIR       ?= .
SRC_DIR         ?= .
INC_DIR         ?= ../../libsrc

APP_SRC         ?= $(shell find -name "*.c") ../boot.S
APP_OBJ         ?= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(notdir $(APP_SRC))))
APP_ELF         ?= $(BUILD_DIR)/app_helloworld.elf
APP_BIN         ?= $(BUILD_DIR)/app_helloworld.bin
APP_HEX         ?= $(BUILD_DIR)/app_helloworld.hex
APP_DISASM      ?= $(APP_ELF).dis

BSP_LIB         ?= $(BUILD_DIR)/libzrbbsp.a

CFLAGS          += -fpic -fpie -O2 -Wall -I$(INC_DIR) \
                    -nostartfiles -nostdlib

LDSCRIPT        ?= ../ldscript.ld

LDFLAGS         += -T$(LDSCRIPT)

all: $(APP_BIN) $(APP_DISASM) $(APP_HEX) $(APP_ELF)

$(APP_DISASM) : $(APP_ELF)
	$(OBJDUMP) -Dt $< > $@

$(APP_BIN) : $(APP_ELF)
	$(OBJCOPY) -O binary $< $@

$(APP_HEX) : $(APP_BIN)
	hexdump -x $< > $@

$(APP_ELF) : $(APP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(BSP_LIB) $(LDFLAGS)

$(BUILD_DIR)/%.c.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.S.o : ../%.S
	$(CC) $(CFLAGS) -c -o $@ $<

