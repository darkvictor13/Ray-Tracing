# O Compilador usado
CC=g++
# flags das libs utilizadas
LIBS=-std=c++17 -O2 -lm

CAMINHO=../src

SRC=$(CAMINHO)/*.cpp 

# como compila o programa
release:
	$(CC) $(SRC) $(LIBS) -o main.out

run: release
	./main.out
