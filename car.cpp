#include "car.h"

Car::Car(sf::Vector2i windowSize, int s) : speed_x(s)
{
	setTexture();
	setSprite();
	this->saveSettings(windowSize);
}

void Car::moveCar(sf::Vector2i windowSize)
{
	if (dir.x == 1)
	{
		sCar.setRotation(10);
		if(sCar.getPosition().x + (sCar.getGlobalBounds().width/2) < windowSize.x) sCar.move(speed_x, 0);
	}
	else if (dir.x == -1)
	{
		sCar.setRotation(-10);
		if (sCar.getPosition().x - (sCar.getGlobalBounds().width/2) > 0) sCar.move(-speed_x, 0);
	}
	else if (dir.x== 0) sCar.setRotation(0);
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

void Car::setDir(sf::Vector2i dx)
{
	dir.x = dx.x;
	dir.y = dx.y;
}

