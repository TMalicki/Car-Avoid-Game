#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"

class Car {
private:
	sf::Texture tCar;
	sf::Sprite sCar;
	int speed_x;

public:
	//sf::Texture chooseCar();
	Car(int s = 5) : speed_x(s) {}
	void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
	void setSprite() { sCar.setTexture(tCar); }
	sf::Sprite& getSprite() { return sCar; }

	void moveCar(int[2]);
	void saveSettings(sf::Vector2i);
};

#endif
