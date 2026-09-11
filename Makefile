# building and testing configuration
CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

TARGET = enconv

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = tests

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

test: $(TARGET)
	@if [ ! -f $(TEST_DIR)/input_cp1251.txt ]; then \
		echo "Error: file $(TEST_DIR)/input_cp1251.txt not found!"; \
		exit 1; \
	fi
	@echo "============ Runinig encoding test ============"
	@echo "input cp1251 file path: $(TEST_DIR)/input_cp1251.txt"
	@echo -n "input cp1251 file text: "
	@cat $(TEST_DIR)/input_cp1251.txt
	@echo ""
	@echo "-----------------------------------------------"
	echo "Running: ./$(TARGET) $(TEST_DIR)/input_cp1251.txt CP-1251 $(TEST_DIR)/output_utf8.txt"
	@./$(TARGET) $(TEST_DIR)/input_cp1251.txt CP-1251 $(TEST_DIR)/output_utf8.txt
	@echo "-----------------------------------------------"
	@echo "output utf8 file path: $(TEST_DIR)/output_utf8.txt"
	@echo -n "output utf8 file text: "
	@cat $(TEST_DIR)/output_utf8.txt
	@echo ""
	@echo "==============================================="


clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_DIR)/output_utf8.txt

.PHONY: all clean test
