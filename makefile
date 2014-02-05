all: main.cpp Analyze.h Analyze.cpp Solve.h Solve.cpp
	mpicxx -std=c++11  main.cpp Analyze.cpp Solve.cpp -o Buddah