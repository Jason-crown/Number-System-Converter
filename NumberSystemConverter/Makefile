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
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET).exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	.\$(TARGET).exe

clean:
	if exist "$(OBJ_DIR)" rmdir /S /Q "$(OBJ_DIR)"
	if exist "$(TARGET).exe" del /Q "$(TARGET).exe"

rebuild: clean all