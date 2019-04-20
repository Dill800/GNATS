#include "pch.h"
#include "Generation.h"


Generation::Generation()
{
}

Generation::Generation(int size, sf::RenderWindow& window, std::vector<Obstacle>& obstacles, CircleShape& lantern) {

	this->size = size;
	gnats = new Gnat[size];

	gen = 1;
	fitnessSum = 0;

	for (int i = 0; i < size; i++) {
		gnats[i] = Gnat(400, window, lantern, obstacles);
	}

	minStep = gnats[0].getBrain()->getSize();



}

void Generation::update() {

	for (int i = 0; i < size; i++) {

		gnats[i].update();

	}

}

void Generation::calculateFitnesses() {

	for (int i = 0; i < size; i++) {

		gnats[i].calculateFitness();

	}

}

bool Generation::allDotsDead() {
	for (int i = 0; i < size; i++) {
		if (!gnats[i].isDead()) {
			return false;
		}
	}
	return true;
}

void Generation::setBestGnat() {

	float max = 0;
	int maxIndex = 0;
	for (int i = 0; i < size; i++) {
		if (gnats[i].getFitness() > max) {
			maxIndex = i;
			max = gnats[i].getFitness();
		}
	}

	bestGnatIndex = maxIndex;

	// If the best reached the goal
	if (gnats[bestGnatIndex].reachedGoal()) {
		minStep = gnats[bestGnatIndex].getBrain()->getStep();
		cout << "Step: " << minStep << endl;
	}

	cout << "Best gnat has a fitness of " << gnats[bestGnatIndex].getFitness() << endl;

}

void Generation::naturalSelection() {

	Gnat* newGnats = new Gnat[size];

	setBestGnat();

	// Sums up all fitnesses of generation
	calculateFitnessSum();

	// best one lives
	newGnats[0] = *gnats[bestGnatIndex].clone();

	//newGnats[0].getBrain()->print();

	//cout << "Stopped midway nat select" << endl;
	//return;

	newGnats[0].setBest();

	//cout << "Best One Lives On" << endl;

	for (int i = 1; i < size; i++) {

		Gnat* parent = selectParent();

		newGnats[i] = *parent;

	}

	delete[] gnats;
	gnats = newGnats;

}

void Generation::calculateFitnessSum() {

	fitnessSum = 0;
	for (int i = 0; i < size; i++) {
		fitnessSum += gnats[i].getFitness();
	}

	cout << "Fitness Sum: " << fitnessSum << endl;


}

Gnat* Generation::selectParent() {

	int random = rand() % (int)fitnessSum;

	int runningSum = 0;

	for (int i = 0; i < size; i++) {
		runningSum += gnats[i].getFitness();

		if (runningSum > random) {
			return gnats[i].clone();
			
		}
	}

	cout << "RETUREND INVALID GNAT" << endl;
	return new Gnat();
}

// Resets for now
void Generation::mutateBrains() {

	for (int i = 1; i < size; i++) {

		gnats[i].newBrain();
		gnats[i].getBrain()->mutate();
	}

}

int Generation::getMinStep() {
	return minStep;
}

Generation::~Generation()
{
}
