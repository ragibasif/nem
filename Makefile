CXX := clang++
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
		  -g3 -O0 -D_GLIBCXX_DEBUG \
		  -DDEBUG=1
LDFLAGS := -stdlib=libc++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# exclude main.cpp from the lib so tests can have their own main
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Targets
MAIN_BIN := $(BIN_DIR)/nem
TEST_BIN := $(BIN_DIR)/nem_tests

.PHONY: default
default: all

.PHONY: all
all: $(MAIN_BIN)

$(MAIN_BIN): main.cpp $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: test
test: $(TEST_BIN)
	@./$(TEST_BIN)

$(TEST_BIN): tests/main.cpp $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run:
	@make clean
	@make all
	@./$(MAIN_BIN)
	@make clean

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
