# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data

# Compiler flags
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target
TARGET = main

# Default Rule
all: $(BUILD_DIR) $(TARGET)

# Link all objects into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile each .c file into .o object
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule for Windows (optional)
clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET).exe 