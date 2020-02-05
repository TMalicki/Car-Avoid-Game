#include "Bullet.h"

Bullet::Bullet(float x)
{
	timeMulitplayer = x;
	setSize(5);
	bullet.setOrigin(5, 5);
	bullet.setFillColor(sf::Color::Red);
	setSpeed(10);
}
