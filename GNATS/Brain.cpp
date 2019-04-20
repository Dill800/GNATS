#include "pch.h"
#include "Brain.h"
#include "math.h"

using namespace sf;
using namespace std;

Brain::Brain(int size)
{

	nudgeSize = size;
	nudges = new Vector2<double>[size];

	randomize();

}

// Deep Copy
Brain* Brain::clone() {

	Brain* clone = new Brain(nudgeSize);

	for (int i = 0; i < nudgeSize; i++) {
		clone->nudges[i] = Vector2<double>(nudges[i].x, nudges[i].y);
	}

	return clone;

}

void Brain::mutate() {

	int rate = 3;
	for (int i = 0; i < nudgeSize; i++) {
		int randInt = rand() % 100;
		if (randInt < rate) {

			int randX = rand() % 100;
			int randY = rand() % 100;

			if (rand() % 2 == 0) {
				randX *= -1;
			}
			if (rand() % 2 == 0) {
				randY *= -1;
			}

			double magnitude = sqrt(pow(randX, 2) + pow(randY, 2));

			nudges[i] = Vector2<double>(randX / magnitude, randY / magnitude);


		}
	}

}

void Brain::incrementStep() {

	step++;

}

int Brain::getStep() {
	return step;
}

void Brain::randomize() {

	for (int i = 0; i < nudgeSize; i++) {

		int randX = rand() % 100;
		int randY = rand() % 100;

		if (rand() % 2 == 0) {
			randX *= -1;
		}
		if (rand() % 2 == 0) {
			randY *= -1;
		}

		double magnitude = sqrt(pow(randX, 2) + pow(randY, 2));

		nudges[i] = Vector2<double>(randX / magnitude, randY / magnitude);

	}

}

bool Brain::incomplete() {

	return step < nudgeSize;

}

Vector2<double> Brain::getCurrentVector() {

	return nudges[step];

}

int Brain::getSize() {
	return nudgeSize;
}

void Brain::print() {
	for (int i = 0; i < nudgeSize; i++) {
		cout << nudges[i].x << " " << nudges[i].y << endl;
	}
}

Brain::~Brain()
{
	delete[] nudges;
}
