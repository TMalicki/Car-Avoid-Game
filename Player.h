#ifndef PLAYER_H
#define PLAYER_H

#include "car.h"

class Player : public Car {
private:
	int points;
	sf::Text txtPoints;
	sf::Font font;

	static int lvl;
public:
	Player(float sX = 8.0, float sY = 0.0);
	virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
	void setText();
	sf::Text getText() { return txtPoints; }
	virtual void startPoint(sf::Vector2i, int);
	virtual void moveCar(sf::Vector2i, float);

	void lvlUp() { lvl++; }
	static int getLvl() { return lvl; }
	bool collision(std::vector<Car*> trafficCar);
	void pointsGather(std::vector<Car*>&, sf::Vector2i);
	int getPoints() { return points; }
};

#endif
