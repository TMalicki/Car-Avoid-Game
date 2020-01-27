#include "car.h"

void Car::moveCar(int dir[2])
{
	if (dir[0] == 1)
	{
		sCar.setRotation(10);
		sCar.move(speed_x, 0);
	}
	else if (dir[0] == -1)
	{
		sCar.setRotation(-10);
		sCar.move(-speed_x, 0);
	}
	else if (dir[0] == 0) sCar.setRotation(0);
}

void Car::saveSettings(sf::Vector2i windowSize)
{
	sf::Vector2f factor{ 0.3, 0.3 };

	float height = sCar.getGlobalBounds().height;
	float width = sCar.getGlobalBounds().width;

	sCar.setOrigin(width/2 ,height/2);
	sCar.setScale(factor);

	sCar.setPosition(windowSize.x / 2, windowSize.y - ((int)height*factor.y/2));
}

