#ifndef PLAYER_H
#define PLAYER_H

#include "car.h"

class Player : public Car {
	private:
		int points;
	public:
		Player(float sX = 8.0, float sY = 0.0) : Car(sX, sY), points(0) {}
		virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
		virtual void startPoint(sf::Vector2i, int);
		virtual void moveCar(sf::Vector2i, float);

		bool collision(std::vector<Car*> trafficCar);
};

#endif
