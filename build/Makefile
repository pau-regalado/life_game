SRC=../src/
INCLUDE=../include/

all: celula rejilla main

celula: $(INCLUDE)celula.h
	g++ $(SRC)celula.cc -c
rejilla: $(INCLUDE)rejilla.h
	g++ $(SRC)rejilla.cc -c
main: celula rejilla
	g++ $(SRC)main.cc celula.o rejilla.o -o main

