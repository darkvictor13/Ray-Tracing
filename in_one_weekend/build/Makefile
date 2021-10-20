CC=g++
LIBS=-lm
FLAGS=-std=c++17 -O2 -c

CAMINHO=../src

SRC=$(CAMINHO)/*/*.cpp $(CAMINHO)/main.cpp
OBJS=./*.o
OUT=main.out

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(OBJS): $(SRC)
	$(CC) $(SRC) $(FLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(OUT)

run: all
	./$(OUT)
