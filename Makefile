CC := gcc
CFLAGS := -Wall -Wextra -o3

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

TARGET := $(BUILD_DIR)/server

# Specify the base names for the source files
SRCS := request.c response.c server.c main.c utils/file.c

# Build the full paths for sources and headers
HEADERS := $(addprefix $(INC_DIR)/, server.h request.h response.h utils/file.h)
SOURCES := $(addprefix $(SRC_DIR)/, $(SRCS))

# Define the object files based on the source files
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

# Rule for creating the build directory
OBJ_DIRS := $(sort $(dir $(OBJECTS)))

.PHONY: all clean

all: $(OBJ_DIRS) $(TARGET)

$(OBJ_DIRS):
	@mkdir -p $@
	@echo "Created directory: $@"

#Pattern rule for compiling C source files into object files
#The dependency is on the source file and all headers.
#This rule depends on the BUILD?DIR being created, hence the order'only prerequisite.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule for linking the object files into the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking files... "
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo "Cleaning up compiled files and build directory..."
	@rm -f $(TARGET) $(OBJECTS)
	@rmdir --ignore-fail-on-non-empty $(OBJ_DIRS) 2>/dev/null || true
