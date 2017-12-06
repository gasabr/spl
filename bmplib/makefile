CC=gcc
LD=gcc
PROG_NAME=bmp_transform
CFLAGS= -std=c99 -pedantic-errors -Wall -Werror
OS_NAME := $(shell uname -s)

# for non-Mac linux
ifneq ($(OS_NAME),Darwin)
	CFLAGS+= -lm
	LFLAGS= -lm
endif
	
BUILD_DIR=./build
SRC_DIR=./src
BIN_DIR=./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
OBJ_LIST = $(patsubst ./src/%.c,./build/%.o,$(SRC_LIST))


all: directories sepia_asm $(PROG_NAME)

directories:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(PROG_NAME): $(OBJ_LIST)
	$(LD) $(LFLAGS) $(OBJ_LIST) $(BUILD_DIR)/sepia.o -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

sepia_asm:
	nasm -felf64 src/sepia.asm -o $(BUILD_DIR)/sepia.o

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o
