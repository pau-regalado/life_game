SRC=../src/
INCLUDE=../include/

all: main

AB:
	g++ $(SRC)AB.cc -c

ABE:
	g++ $(SRC)ABE.cc -c

main:
	g++ $(SRC)main.cc -o main

clean:
	rm main
	g++ $(SRC)main.cc AB.o ABE.o -o main
	./main