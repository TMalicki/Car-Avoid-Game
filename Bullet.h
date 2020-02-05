#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape bullet;
	int recoil;
	float speed;
	int size;
	float timeMulitplayer;
public:
	Bullet(float x = 30);
	void setSize(int x) { bullet.setRadius(x); }
	void setSpeed(float x) { speed = x; }
	float getSpeed() const { return speed; }
	void move(sf::Vector2i windowSize, float dt) { bullet.move(0, -dt * timeMulitplayer * speed); }
	void position(float x, float y) { bullet.setPosition(x, y); }
	sf::CircleShape& getBullet() { return bullet; }
};

#endif