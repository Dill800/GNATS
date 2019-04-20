#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

using namespace sf;

class Brain
{

	Vector2<double>* nudges;
	int nudgeSize;
	int step;

public:
	Brain(int size);

	// Initializes random vectors with length of 1
	void randomize();

	// Returns copy of this object
	Brain* clone();

	// Sets some of directions to random vectors
	void mutate();

	void incrementStep();

	// returns true if steps are still to be taken
	bool incomplete();

	Vector2<double> getCurrentVector();

	int getStep();

	void print();

	int getSize();

	~Brain();
};

