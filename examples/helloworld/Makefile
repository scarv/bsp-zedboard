
BUILD_DIR       ?= .
SRC_DIR         ?= .
INC_DIR         ?= ../../libsrc

APP_SRC         ?= $(shell find -name "*.c")
APP_OBJ         ?= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(APP_SRC)))
APP_EXE         ?= $(BUILD_DIR)/app_helloworld
APP_DISASM      ?= $(APP_EXE).dis

BSP_LIB         ?= $(BUILD_DIR)/libzrbbsp.a

CFLAGS          += -fpic -fpie -O2 -Wall -I$(INC_DIR) \
                    -nostartfiles -nostdlib

LDSCRIPT        ?= ../ldscript.ld

LDFLAGS         += -T$(LDSCRIPT)

all: $(APP_EXE) $(APP_DISASM)

$(APP_DISASM) : $(APP_EXE)
	$(OBJDUMP) -Dt $< > $@

$(APP_EXE) : $(APP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(BSP_LIB) $(LDFLAGS)

$(BUILD_DIR)/%.c.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

