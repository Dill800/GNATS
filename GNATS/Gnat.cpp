#include "pch.h"
#include "Gnat.h"

Gnat::Gnat() {

}

Gnat::Gnat(Gnat& gnat) {



}

Gnat::Gnat(int brainSize, sf::RenderWindow& window, CircleShape& lantern, std::vector<Obstacle>& obstacles)
{

	windowPtr = &window;
	obstaclesPtr = &obstacles;
	lanternPtr = &lantern;

	body = CircleShape(3);

	position = sf::Vector2<double>(windowPtr->getSize().x / 2, windowPtr->getSize().y * (5.0/6));
	velocity = sf::Vector2<double>(0, 0);
	acceleration = sf::Vector2<double>(0, 0);

	body.setPosition(position.x, position.y);

	body.setOrigin(Vector2<float>(body.getRadius(), body.getRadius()));

	this->brainSize = brainSize;
	brain = new Brain(brainSize);

}

// kinda temp ish
void Gnat::newBrain() {

	/*if (brain != nullptr) {
		delete brain;
		brain = new Brain(brainSize);
	}*/

	dead = false;
	reachedGoalVar = false;

	position.x = windowPtr->getSize().x / 2; position.y = windowPtr->getSize().y * (5.0/6);

	//windowPtr->getSize().x / 2, windowPtr->getSize().y * (5.0/6)

	velocity.x = 0; velocity.y = 0;

}

// draw gnat on screen
void Gnat::show() {

}

// move dot based on brain
void Gnat::move() {

	if (brain->incomplete()) {

		acceleration = brain->getCurrentVector();

		brain->incrementStep();

	}
	else {
		dead = true;
	}

	velocity += acceleration;

	// Limits velocity
	if ((int)velocity.x > 5) {
		velocity.x = 5;
	}
	else if ((int)velocity.x < -5) {
		velocity.x = -5;
	}
	if ((int)velocity.y > 5) {
		velocity.y = 5;
	}
	else if ((int)velocity.y < -5) {
		velocity.y = -5;
	}

	position += velocity;

	body.setPosition(position.x, position.y);


	windowPtr->draw(body);


}

// calls move, check collisions
void Gnat::update() {

	if (!dead && !reachedGoalVar) {
		
		move();

		// Bounds check, if near edges kill
		if ((int)position.x < (int)body.getRadius()) {
			dead = true;
			position.x = body.getRadius();
		}
		if ((int)position.x >= windowPtr->getSize().x - (int)body.getRadius()) {
			dead = true;
			position.x = windowPtr->getSize().x - (int)body.getRadius();
		}
		if ((int)position.y < body.getRadius()) {
			dead = true;
			position.y = body.getRadius();
		}
		if ((int)position.y >= windowPtr->getSize().y - body.getRadius()) {
			dead = true;
			position.y = windowPtr->getSize().y - body.getRadius();
		}
		

		// if reached goal then make reachedgoal true
		if (sqrt(pow((int)position.x - (int)lanternPtr->getPosition().x, 2) + pow((int)position.y - (int)lanternPtr->getPosition().y, 2)) <= lanternPtr->getRadius()) {
			reachedGoalVar = true;
			//cout << "Steps: " << brain->getStep() << endl;

			dead = true;
		}

		// If hit obstacle then make it die
		for (int i = 0; i < obstaclesPtr->size(); i++) {

			if (obstaclesPtr->at(i).contains(*this)) {
				dead = true;
			}

		}
	}

	if (dead) {
		windowPtr->draw(body);
	}
	

}

void Gnat::setDead() {
	dead = true;
}

void Gnat::calculateFitness() {

	if (reachedGoalVar) {

		//fitness = 10.0 + 10000.0 / (float)(pow(brain->getStep(), 2));

		float longestDistance = sqrt(pow(lanternPtr->getPosition().x - windowPtr->getSize().x, 2) + pow(lanternPtr->getPosition().y - windowPtr->getSize().y, 2));

		fitness = (int)longestDistance + (int)((brain->getSize() * longestDistance) / (brain->getStep()*brain->getStep()));

		fitness = (int)longestDistance + longestDistance * (int)( brain->getSize() - brain->getStep() )/6;

		//fitness = longestDistance + pow(brain->getSize() / brain->getStep(), 2);

		//fitness = (int)pow(longestDistance/lanternPtr->getRadius(), 2) + (brain->getSize() / brain->getStep()) * (int)pow(longestDistance / lanternPtr->getRadius(), 2);

		//fitness = (int)pow(longestDistance / lanternPtr->getRadius(), 2) + (int)(brain->getSize() - brain->getStep()) * (int)pow(longestDistance/brain->getStep(), 2);

		//fitness = (int)pow(longestDistance / lanternPtr->getRadius(), 2) * (int)(brain->getSize() - brain->getStep());

	}
	else {

		float longestDistance = sqrt( pow(lanternPtr->getPosition().x - windowPtr->getSize().x, 2) + pow(lanternPtr->getPosition().y - windowPtr->getSize().y, 2));

		float actualDistance = sqrt(pow(lanternPtr->getPosition().x - position.x, 2) + pow(lanternPtr->getPosition().y - position.y, 2));

		// Should never be 0 because radius us greater than 1
		if ((int)actualDistance == 0) {
			fitness = (int)longestDistance;
		}
		else {
			/*fitness = (int)(longestDistance / actualDistance);*/

			fitness = (int)(longestDistance / actualDistance);
			//fitness = (int)pow(fitness, 2);

		}

		

		//fitness = 10.0 / pow(distanceToGoal, 2);

	}

}

bool Gnat::isDead() {
	return dead;
}

Vector2<double> Gnat::getPos() {
	return position;
}

Gnat* Gnat::clone() {

	Gnat* clone = new Gnat(brainSize, *windowPtr, *lanternPtr, *obstaclesPtr);
	
	clone->setBrain(this->brain);

	clone->setFitness(this->fitness);

	return clone;
}

void Gnat::setBrain(Brain* brain) {
	this->brain = brain->clone();
}

void Gnat::setFitness(int fitnessNum) {
	fitness = fitnessNum;
}

void Gnat::setBest() {
	this->bestGnat = true;
}

Brain* Gnat::getBrain() {
	return brain;
}

double Gnat::getFitness() {

	return fitness;

}

bool Gnat::isBest() {
	return bestGnat;
}

bool Gnat::reachedGoal() {
	return reachedGoalVar;
}

Gnat::~Gnat()
{
}
