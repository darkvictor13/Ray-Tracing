# O Compilador usado
CC=g++
# flags das libs utilizadas
LIBS=-lm
FLAGS=-std=c++17 -O2 -c

CAMINHO=../src

SRC=$(CAMINHO)/*.cpp 
OBJS=./*.o
OUT=main.out

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(OBJS): $(SRC)
	$(CC) $(SRC) $(FLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(OUT)

run: release
	./main.out
