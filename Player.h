#ifndef PLAYER_H
#define PLAYER_H

#include "car.h"
#include "Bullet.h"

class Player : public Car {
private:
	int score;
	sf::Text tScore;
	sf::Font font;

	sf::Vector2f topLeftCorner;
	sf::Vector2f topRightCorner;
	sf::Vector2f bottomLeftCorner;
	sf::Vector2f bottomRightCorner;

	sf::VertexArray* collisionArea;
	///std::vector<sf::Vector2f> narrowPoints;

	static int lvl;

	Bullet bullet;
	//int bulletAmount;
	//int bulletMaxAmount;
public:
	Player(float sX = 12.0, float sY = 0.0);

	virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
	void setText();
	sf::Text getText() { return tScore; }
	
	void lvlUp(std::vector<Car*> trafficCar);
	static int getLvl() { return lvl; }

	virtual void startPoint(sf::Vector2i, int);
	virtual void moveCar(sf::Vector2i, float);

	void calculateCollisionArea();
	sf::VertexArray getCollisionArea() { return *collisionArea; }

	bool collision(std::vector<Car*> trafficCar);

	void pointsGather(std::vector<Car*>&, sf::Vector2i);
	int getPoints() { return score; }

	void shoot();
	sf::CircleShape& getBullet() { return bullet.getBullet(); }
};

#endif
