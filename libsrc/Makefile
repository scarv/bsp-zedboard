
BUILD_DIR       ?= ../build
SRC_DIR         ?= .

LIB_SRC         ?= $(shell find -name "*.c")
LIB_OBJ         ?= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(LIB_SRC)))
LIB_STATIC      ?= $(BSP_LIB)

CFLAGS          += -fpic -O2 -Wall


all: $(LIB_STATIC)

$(LIB_STATIC) : $(LIB_OBJ)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.c.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
