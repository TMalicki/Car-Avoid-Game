#ifndef PLAYER_H
#define PLAYER_H

#include "car.h"

class Player : public Car {
private:
	int points;
public:
	Player(sf::Vector2i windowSize, int speed = 5) : Car(windowSize, speed), points(0) {}
	virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
	virtual void startPoint(sf::Vector2i, int);
	virtual void moveCar(sf::Vector2i, float);
};

#endif
