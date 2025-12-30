SRC_DIR := src
BUILD_DIR := build
CC := clang++
CXXFLAGS := -std=c++20 \
		  -pedantic -Wall -Wextra -Wvla -Wshadow \
		  -Wno-unused-parameter -Wwrite-strings -Wstrict-prototypes \
		  -Wold-style-cast -Wredundant-decls -Wnested-externs \
		  -Wmissing-include-dirs \
		  -Wconversion -Wfloat-equal -Wswitch -Wimplicit-fallthrough \
		  -fno-sanitize-recover -fsanitize=address -fsanitize=undefined \
		  -fno-omit-frame-pointer -fno-optimize-sibling-calls \
		  -fstack-protector-all -Wstack-protector \
		  -MMD -MP \
		  -stdlib=libc++ \
		  -g3 -O0 -DDEBUG=1 -D_GLIBCXX_DEBUG \
		  -DTEST=1

LDFLAGS := # -lm  -I some/path/to/library


SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET := $(BUILD_DIR)/nem

.PHONY: default
default: all

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run:
	@make clean
	@make all
	./$(TARGET)
	@make clean

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
