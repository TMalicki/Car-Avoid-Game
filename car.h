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

	sf::Vector2i dir;
	const float timeMultiply = 31.25;
	/// ///////////////////////////////////////
	sf::Vector2f speed;

public:
	//sf::Texture chooseCar();
	Car(float, float);

	void loadSprite() {
		setTexture();
		setSprite();
	}

	void setSprite() { sCar.setTexture(tCar); }
	sf::Sprite& getSprite() { return sCar; }

	virtual void setTexture() = 0;
	virtual void startPoint(sf::Vector2i, int) = 0;
	virtual void moveCar(sf::Vector2i, float) = 0;

	void setSpeed(float speed_x, float speed_y) { speed.x = speed_x; speed.y = speed_y; }
	sf::Vector2f getSpeed() { return speed; }
	void saveSettings(sf::Vector2i);
	void setDir(sf::Vector2i);
	sf::Vector2i getDir() { return dir; }
};

#endif
