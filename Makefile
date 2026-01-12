CXX := clang++
CXXSTD := -std=c++23

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := built
OBJ_DIR := obj

RELEASE_BIN := $(BUILD_DIR)/Hamster
DEBUG_BIN := $(BUILD_DIR)/HamsterD

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

WARNINGS := -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-gnu-zero-variadic-macro-arguments -Wno-unused-but-set-variable
INCLUDES := -I$(INC_DIR)

RELEASE_FLAGS := -O2 -flto
DEBUG_FLAGS := -g -O0 -DDEBUG
DEPFLAGS := -MMD -MP

all: release

release: $(RELEASE_BIN)

$(RELEASE_BIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXSTD) $(WARNINGS) $(INCLUDES) $(RELEASE_FLAGS) $^ -o $@

debug: $(DEBUG_BIN)

$(DEBUG_BIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXSTD) $(WARNINGS) $(INCLUDES) $(DEBUG_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXSTD) $(WARNINGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: release
	@cd $(BUILD_DIR) && ./Hamster $(ARGS) || true

run-debug: debug
	@cd $(BUILD_DIR) && ./HamsterD $(ARGS) || true

clean:
	rm -rf $(BUILD_DIR)

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

.PHONY: all release debug run run-debug clean
