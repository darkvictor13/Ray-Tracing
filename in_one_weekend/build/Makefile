CC=g++

LIBS=-lm

CXXFLAGS=-std=c++17 -c
# para executar mais rápido
CXXFLAGS += -O3
# para degugar com gdb
# CXXFLAGS += -g


CAMINHO=../src

SRC=$(CAMINHO)/*/*.cpp $(CAMINHO)/main.cpp
OBJS=./*.o
OUT=main.out

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(OBJS): $(SRC)
	$(CC) $(SRC) $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(OUT)

run: all
	./$(OUT)
