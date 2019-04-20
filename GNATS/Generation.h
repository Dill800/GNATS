#pragma once
#include <SFML/Graphics.hpp>
#include "Gnat.h"

class Generation
{

private:
	Gnat* gnats;
	int size;
	float fitnessSum;

	int bestGnatIndex = 0;

	int gen;
	int minStep;

public:
	Generation();

	Generation(int size, sf::RenderWindow& window, std::vector<Obstacle>&, CircleShape&);

	void update();

	void calculateFitnesses();

	// Determines if the dots are all dead
	bool allDotsDead();

	void naturalSelection();

	void calculateFitnessSum();

	void setBestGnat();

	Gnat* selectParent();

	void mutateBrains();

	int getMinStep();

	~Generation();
};

