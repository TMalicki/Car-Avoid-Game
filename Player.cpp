#include "Player.h"
#include <string>

int Player::lvl = 0;

Player::Player(float sX, float sY) : Car(sX, sY), points(0) {
	font.loadFromFile("fonts/QuiteMagical.ttf");

	txtPoints.setFont(font);
	txtPoints.setCharacterSize(20);
	txtPoints.setFillColor(sf::Color::White);
	txtPoints.setPosition(10, 10);
}

void Player::setText()
{
	std::string temp = "Points: " + std::to_string(points);
	txtPoints.setString(temp);
}

void Player::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	sCar.setPosition(windowSize.x / 2, windowSize.y - carCorrection);
}

void Player::moveCar(sf::Vector2i windowSize, float dt)
{
	static int counter = 0;
	if (dir.x == 1)
	{
		sCar.setRotation(10);
		if (sCar.getPosition().x + (sCar.getGlobalBounds().width / 2) < windowSize.x) sCar.move(speed.x * dt * timeMultiply, 0.0);
	}
	else if (dir.x == -1)
	{
		sCar.setRotation(-10);
		if (sCar.getPosition().x - (sCar.getGlobalBounds().width / 2) > 0) sCar.move(-speed.x * dt * timeMultiply, 0.0);
	}
	else if (dir.x == 0) sCar.setRotation(0);

	/* -------------------------------------------   */
	counter++;
	if (counter == 50) {
	std::cout << "Corner pos: " << sCar.getGlobalBounds().left << " " << sCar.getGlobalBounds().left + sCar.getGlobalBounds().width << std::endl;
	std::cout << "Center pos: " << sCar.getOrigin().x << std::endl;
	counter = 0;
	/* -------------------------------------------   */
	}
}

void Player::lvlUp(std::vector<Car*> trafficCar)
{
	if (points % 10 == 0) {
		lvl++; 
	}
}

bool Player::collision(std::vector<Car*> trafficCar)
{
	bool state = 0;
	int size = trafficCar.size();
	
	while (size-- && state == false)
		if (this->getSprite().getGlobalBounds().intersects(trafficCar[size]->getSprite().getGlobalBounds())) return true;
}

void Player::pointsGather(std::vector<Car*>& trafficCar, sf::Vector2i windowSize)
{
	if ((*trafficCar.begin())->getSprite().getGlobalBounds().top >= windowSize.y)
	{
		points++;
		trafficCar.erase(trafficCar.begin());
		lvlUp(trafficCar);
	}
}
