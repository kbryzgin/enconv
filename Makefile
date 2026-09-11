CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

TARGET = enconv

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/encoding.o

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/encoding.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/encoding.o: $(SRC_DIR)/encoding.c $(INC_DIR)/encoding.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/encoding.c -o $(BUILD_DIR)/encoding.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
