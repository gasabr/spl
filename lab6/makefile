CC=gcc
LD=gcc
PROG_NAME=main
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


all: directories $(PROG_NAME)

directories:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(PROG_NAME): $(OBJ_LIST)
	$(LD) $(LFLAGS) $(OBJ_LIST) -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o

run:
	$(BIN_DIR)/$(PROG_NAME)
