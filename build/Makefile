SRC=../src/
INCLUDE=../include/

all: celula rejilla state main

celula: $(INCLUDE)celula.h
	g++ $(SRC)celula.cc -c
rejilla: $(INCLUDE)rejilla.h
	g++ $(SRC)rejilla.cc -c
state: $(INCLUDE)state.h
	g++ $(SRC)state.cc -c	
main: celula rejilla
	g++ $(SRC)main.cc celula.o rejilla.o state.o -o main

