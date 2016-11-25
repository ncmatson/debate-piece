CC = g++
SRCDIR = src

debate:
	g++ -std=c++11 -o bin/debate $(SRCDIR)/*.cpp
