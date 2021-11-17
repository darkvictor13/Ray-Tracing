CXX=g++

LDFLAGS=-lm -lpthread

CXXFLAGS= -std=c++17 -Wall -Wextra
#warnings tradados como erro:
# CXXFLAGS += -Werror

# para executar mais rápido:
CXXFLAGS += -O3

# para degugar com gdb:
# CXXFLAGS += -g

# Checar memory leaks:
CXXFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

# Somente usar coisas do C++ ISO proibe structs anônimas
# CXXFLAGS += -pedantic

SRC_DIR=../src
OBJ_DIR=./objs

SRC := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
PCH := $(wildcard $(SRC_DIR)/pch/*.hpp $(SRC_DIR)/headers/*.hpp)

OUT=main.out

.PHONY:all clean deploy p run

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT)

deploy:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

p:
	$(CXX) $(CXXFLAGS) $(PCH)

run: all
	./$(OUT)

