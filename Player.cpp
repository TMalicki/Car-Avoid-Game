#include "Player.h"

void Player::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	sCar.setPosition(windowSize.x / 2, windowSize.y - carCorrection);
}


void Player::moveCar(sf::Vector2i windowSize, float dt)
{
	if (dir.x == 1)
	{
		sCar.setRotation(10);
		if (sCar.getPosition().x + (sCar.getGlobalBounds().width / 2) < windowSize.x) sCar.move(speed_x * dt * timeMultiply, 0);
	}
	else if (dir.x == -1)
	{
		sCar.setRotation(-10);
		if (sCar.getPosition().x - (sCar.getGlobalBounds().width / 2) > 0) sCar.move(-speed_x * dt * timeMultiply, 0);
	}
	else if (dir.x == 0) sCar.setRotation(0);
}
