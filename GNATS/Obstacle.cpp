#include "pch.h"
#include "Obstacle.h"

#include "Gnat.h"

using namespace sf;

Obstacle::Obstacle()
{
}

// xPos, yPos, sizeX, sizeY
Obstacle::Obstacle(int xPos, int yPos, int sizeX, int sizeY) {

	this->xPos = xPos;
	this->yPos = yPos;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	obj.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
	obj.setOutlineColor(Color::White);

	obj.setPosition(xPos, yPos);
	obj.setSize(Vector2<float>(sizeX, sizeY));

}

bool Obstacle::contains(Gnat& gnat) {

	if (gnat.getPos().x <= xPos + sizeX && gnat.getPos().x >= xPos) {
		if (gnat.getPos().y <= yPos + sizeY && gnat.getPos().y >= yPos) {

			return true;

		}
	}

	return false;

}

RectangleShape& Obstacle::getObstacle() {
	return obj;
}


Obstacle::~Obstacle()
{
}
