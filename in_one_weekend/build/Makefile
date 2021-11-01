CC=g++

LIBS=-lm -lpthread

CXXFLAGS= -std=c++20 -c
# para executar mais rápido
CXXFLAGS += -O3
# para degugar com gdb
# CXXFLAGS += -g


CAMINHO=../src

SRC=$(CAMINHO)/*/*.cpp $(CAMINHO)/main.cpp
OBJS=./*.o
OUT=main.out

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

$(OBJS): $(SRC)
	$(CC) $(SRC) $(CXXFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: all
	./$(OUT)
