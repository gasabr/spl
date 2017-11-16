CC=gcc
LD=gcc
PROG_NAME=bmp_transform
CFLAGS= -std=c99 -pedantic-errors -Wall -Werror

ifneq ($(OS),Darwin)
	CFLAGS+= -lm
endif
	
BUILD_DIR=./build
SRC_DIR=./src
BIN_DIR=./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
OBJ_LIST = $(patsubst ./src/%.c,./build/%.o,$(SRC_LIST))


all: $(PROG_NAME)

$(PROG_NAME): $(OBJ_LIST)
	$(LD) $(OBJ_LIST) -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o
