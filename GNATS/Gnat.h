#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Brain.h"
#include <vector>
#include "Obstacle.h"

using namespace std;
using namespace sf;

class Gnat
{

private:

	CircleShape body;

	Vector2<double> position;
	Vector2<double> velocity;
	Vector2<double> acceleration;

	// Brain
	Brain* brain;
	sf::RenderWindow* windowPtr;
	vector<Obstacle>* obstaclesPtr;
	CircleShape* lanternPtr;
	int brainSize;

	// States
	bool dead = false;
	bool reachedGoalVar = false;
	bool bestGnat = false;

	double fitness = 0;

public:

	Gnat();

	Gnat(Gnat& gnat);

	Gnat(int, sf::RenderWindow& window, CircleShape&, std::vector<Obstacle>& obstacles);

	// draw gnat on screen
	void show();

	// move dot based on brain
	void move();

	// calls move, check collisions
	void update();

	void calculateFitness();

	bool isDead();

	Vector2<double> getPos();

	Gnat* clone();

	void setDead();

	void newBrain();

	Brain* getBrain();

	double getFitness();

	bool isBest();

	bool reachedGoal();

	void setFitness(int);

	void setBest();

	void setBrain(Brain* brain);

	sf::RenderWindow& getWindowPtr();



	~Gnat();
};

