CC = gcc
CFLAGS = -Wall -g

# Directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_TARGETS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%)

# Library object (excluding main.c)
LIB_SRCS = $(filter-out $(SRC_DIR)/main.c, $(SRCS))
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean test

all: $(BUILD_DIR)/main $(TEST_TARGETS)

test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS) ; do \
		./$$test ; \
	done

$(BUILD_DIR)/main: $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(LIB_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $@ -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
