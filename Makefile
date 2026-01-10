CXX := clang++
CXXSTD := -std=c++23

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := built

RELEASE_BIN := $(BUILD_DIR)/Hamster
DEBUG_BIN := $(BUILD_DIR)/HamsterD

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

WARNINGS := -Wall -Wextra -Wpedantic
INCLUDES := -I$(INC_DIR)

RELEASE_FLAGS := -O2 -flto
DEBUG_FLAGS := -g -O0

all: release

release: $(RELEASE_BIN)

$(RELEASE_BIN): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXSTD) $(WARNINGS) $(INCLUDES) $(RELEASE_FLAGS) $^ -o $@

debug: $(DEBUG_BIN)

$(DEBUG_BIN): $(SRCS) | $(BUILD_DIR)
	$(CXX) $(CXXSTD) $(WARNINGS) $(INCLUDES) $(DEBUG_FLAGS) $^ -o $@

run: release
	./$(RELEASE_BIN)

run-debug: debug
	./$(DEBUG_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all release debug run run-debug clean
