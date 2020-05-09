FLAGS = -pedantic-errors -std=c++11

game.o: game.cpp structure.h
	g++ $(FLAGS) -c $<

main.o: main.cpp structure.h
	g++ $(FLAGS) -c $<

gamer: main.o game.o 
	g++ $(FLAGS) $^ -o $@

clean: 
	rm -rf *.o *.dat

.PHONY: clean
