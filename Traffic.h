#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "Car.h"
#include <cstdlib>

class Traffic : public Car {
	private:
		//static int lvl;
		//enum positions {first = 50, second = 150, third = 250, fourth = 350, fifth = 450};
	public:
		Traffic(float sX = 0.0, float sY = 9.0) : Car(sX, sY) { }
		virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
		virtual void startPoint(sf::Vector2i, int);
		virtual void moveCar(sf::Vector2i, float);

		
	};

#endif

