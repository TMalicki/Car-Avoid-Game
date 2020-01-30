#include "Traffic.h"

int Traffic::lvl = 1;

void Traffic::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	int line = std::rand() % 5 + 0;

	sCar.rotate(180.0);
	sCar.setPosition(50 + 100*line, 0);
}

void Traffic::moveCar(sf::Vector2i windowSize, float dt)
{
	std::cout << speed.y << std::endl;
	sCar.move(0, dt * timeMultiply * speed.y);
}
