// GNATS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Gnat.h"
#include "Generation.h"
#include "Obstacle.h"

using namespace sf;
using namespace std;

int main()
{
	srand(time(0));
	
	sf::RenderWindow window(sf::VideoMode(1600, 900), "GNATS");
	window.setFramerateLimit(70);

	// Create Obstacles
	vector<Obstacle> obstacles;
	obstacles.push_back(Obstacle(30, 30, 30, 30));
	obstacles.push_back(Obstacle(400, 500, 100, 200));
	obstacles.push_back(Obstacle(400, 400, 600, 50));

	// Create Lantern
	CircleShape lantern(10);

	// Create Generation
	Generation g(400, window, obstacles, lantern);

	// DEBUGGING

	//Brain* brain = new Brain(40);
	Gnat* gnat = new Gnat(40, window, lantern, obstacles);

	Gnat* clonedGnat = gnat->clone();

	//return 1;


	sf::Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		window.clear(sf::Color::Black);




		// Draw everything here
		if (!g.allDotsDead()) {
			//cout << "Updating" << endl;
			g.update();
		}
		else {
			cout << "ALL GNATS HAVE DIED" << endl;

			// Calculate Fitness
			g.calculateFitnesses(); // Works


			// Run Natural Selection
			g.naturalSelection();


			// Mutate Babies
			g.mutateBrains();


		}
		

		// Draw the lantern
		lantern.setPosition(window.getSize().x/2, 2*lantern.getRadius());
		lantern.setOrigin(Vector2<float>(lantern.getRadius(), lantern.getRadius()));
		lantern.setFillColor(Color::Cyan);
		window.draw(lantern);
		

		// Draw the obstacles
		for (int i = 0; i < obstacles.size(); i++) {

			window.draw(obstacles[i].getObstacle());

		}

		// Test if all of the gnats are dead
		// If they are ddead calculate fitness, natural selection, mutate
		// If they are still alive then update generation and show them
		

		window.display();

	}

	


	return 0;
}