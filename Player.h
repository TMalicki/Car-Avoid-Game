#ifndef PLAYER_H
#define PLAYER_H

#include "car.h"
#include "Bullet.h"
#include <vector>

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

	int bulletAmount = 0;
	int bulletMaxAmount = 5;
	std::vector<Bullet> bullet;

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
	bool collisionSAT(Car*);

	void pointsGather(std::vector<Car*>&, sf::Vector2i);
	int getPoints() { return score; }

	void shoot(sf::Vector2i windowSize, float dt);
	void reload();
	int getBulletSize() { return bullet.size(); }
	sf::CircleShape& getBullet(int i) { return bullet[i].getBullet(); }
	sf::CircleShape& getMagazine() { return magazine; }
	Bullet& getBulletObj(int i) { return bullet[i]; }
};

#endif
