CC = gcc
CFLAGS = -W -Wall -Wextra -std=c11
SRC_DIR = src
BUILD_DIR = build

.PHONY: all clean

all: $(BUILD_DIR)/parent $(BUILD_DIR)/child

$(BUILD_DIR)/parent: $(SRC_DIR)/parent.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/child: $(SRC_DIR)/child.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/parent $(BUILD_DIR)/child