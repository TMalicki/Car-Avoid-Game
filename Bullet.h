#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape bullet;
	static const int recoil = 50;
	static int actualTimeToRecoil;
	float speed;
	int size;
	float timeMulitplayer;
public:
	Bullet(float x = 30);
	void setSize(int x) { bullet.setRadius(x); }
	void setSpeed(float x) { speed = x; }
	float getSpeed() const { return speed; }
	void move(sf::Vector2i windowSize, float dt);
	void position(float x, float y) { bullet.setPosition(x, y); }
	sf::CircleShape& getBullet() { return bullet; }
	static bool Recoil();
	static int getTimeToRecoil() { return actualTimeToRecoil; }
	static void setTimeToRecoil(int x) { actualTimeToRecoil = x; }

	static int getRecoil() { return recoil; }
	float getPosition() { return bullet.getPosition().y; }
};

#endif