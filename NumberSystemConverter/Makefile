CC := gcc

CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -Iinclude

TARGET := converter

SRC_DIR := src
OBJ_DIR := build

SOURCES := $(SRC_DIR)/main.c \
           $(SRC_DIR)/converter.c

OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

rebuild: clean all