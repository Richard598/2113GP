FLAGS = -pedantic-errors -std=c++11

all: main run clean

main: main.o terminal.o game.o 
	g++ $(FLAGS) $^ -o $@ 

terminal.o: terminal.cpp terminal.h
	g++ $(FLAGS) -c $<

game.o: game.cpp game.h art.h
	g++ $(FLAGS) -c $<

main.o: main.cpp main.h
	g++ $(FLAGS) -c $<

run:
	./main
clean: 
	rm -f *.o main

.PHONY: clean run all
