all: puzzle_solver 

puzzle_solver:
	g++ Main.cpp Board.cpp
	
run:
	./a.out