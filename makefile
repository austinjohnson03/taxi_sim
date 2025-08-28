CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-system -lsfml-window

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARG = $(BIN_DIR)/demo

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

SFML_HDR := $(wildcard /usr/include/SFML/Graphics.hpp)

ifeq ($(SFML_HDR),)
$(error SFML headers not found! Please install libsfml-dev)
endif

all: $(TARG)

$(TARG): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

