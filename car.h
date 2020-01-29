#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "settings.h"

class Car {
protected:
	sf::Texture tCar;
	sf::Sprite sCar;

	float height;
	float width;

	int speed_x;
	sf::Vector2i dir;
	const float timeMultiply = 31.25;
public:
	//sf::Texture chooseCar();
	Car(int s = 5);

	void loadSprite() {
		setTexture();
		setSprite();
	}

	void setSprite() { sCar.setTexture(tCar); }
	sf::Sprite& getSprite() { return sCar; }

	virtual void setTexture() = 0;
	virtual void startPoint(sf::Vector2i, int) = 0;
	virtual void moveCar(sf::Vector2i, float) = 0;

	void saveSettings(sf::Vector2i);
	void setDir(sf::Vector2i);
	sf::Vector2i getDir() { return dir; }
};

#endif
