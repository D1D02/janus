CC := gcc
CFLAGS := -Wall -Wextra -o3

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

TARGET := $(BUILD_DIR)/example

# Specify the base names for the source files
SRCS := main.c server.c
# Build the full paths for sources and headers
SOURCES := $(addprefix $(SRC_DIR)/, $(SRCS))
HEADERS := $(addprefix $(INC_DIR)/, server.h)

# Define the object files based on the source files
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean
all: $(BUILD_DIR) $(TARGET)

# Rule for creating the build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "Created directory: $(BUILD_DIR)"

# Pattern rule for compiling C source files into object files
# The dependency is on the source file and all headers.
# This rule depends on the BUILD_DIR being created, hence the order-only prerequisite.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule for linking the object files into the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking files... "
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo "Cleaning up compiled files and build directory..."
	@rm -f $(TARGET) $(OBJECTS)
	@rmdir --ignore-fail-on-non-empty $(BUILD_DIR) 2>/dev/null || true
