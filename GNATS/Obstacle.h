#pragma once
#include <SFML/Graphics.hpp>
//#include "Gnat.h"
class Gnat;

using namespace sf;

class Obstacle
{

	int xPos;
	int yPos;
	int sizeX;
	int sizeY;

	RectangleShape obj;

public:
	Obstacle();

	// xPos, yPos, sizeX, sizeY
	Obstacle(int, int, int, int);

	RectangleShape& getObstacle();

	bool contains(Gnat& gnat);

	~Obstacle();
};

