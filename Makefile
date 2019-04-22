# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o FBullCowGame.o
	@ $(CXX) $(CXXFLAGS) -o main main.o FBullCowGame.o

# The main.o target can be written more simply

main.o: main.cpp FBullCowGame.h
	@ $(CXX) $(CXXFLAGS) -c main.cpp

FBullCowGame.o: FBullCowGame.cpp
	@ $(CXX) $(CXXFLAGS) -c FBullCowGame.cpp