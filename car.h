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
	sf::Vector2i dir;
public:
	//sf::Texture chooseCar();
	Car(sf::Vector2i, int s = 5);
	void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
	void setSprite() { sCar.setTexture(tCar); }
	sf::Sprite& getSprite() { return sCar; }

	void moveCar(sf::Vector2i);
	void saveSettings(sf::Vector2i);
	void setDir(sf::Vector2i);
	sf::Vector2i getDir() { return dir; }
};

#endif
