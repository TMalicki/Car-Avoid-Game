#include "car.h"

Car::Car(float sX, float sY)
{
	setSpeed(sX, sY);
	//this->saveSettings(windowSize);
}

void Car::saveSettings(sf::Vector2i windowSize)
{
	sf::Vector2f factor{ 0.3, 0.3 };

	this->loadSprite();

	height = sCar.getGlobalBounds().height;
	width = sCar.getGlobalBounds().width;

	sCar.setOrigin(width / 2, height / 2);
	sCar.setScale(factor);

	startPoint(windowSize, (int)height * factor.y / 2);
}

void Car::setDir(sf::Vector2i dx)
{
	dir.x = dx.x;
	dir.y = dx.y;
}

