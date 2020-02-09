#include "Bullet.h"
#include <iostream>

int Bullet::actualTimeToRecoil = 0;

Bullet::Bullet(float x)
{
	timeMulitplayer = x;
	setSize(5);
	bullet.setOrigin(5, 5);
	bullet.setFillColor(sf::Color::Transparent);
	setSpeed(10);
}

void Bullet::move(sf::Vector2i windowSize, float dt)
{
		bullet.setFillColor(sf::Color::Red);
		bullet.move(0, -dt * timeMulitplayer * speed);
	//if(bullet.getPosition().y > 0) 
}

bool Bullet::Recoil()
{
	actualTimeToRecoil++;

	if (actualTimeToRecoil >= recoil)
	{
		actualTimeToRecoil = 0;
		return true;
	}
	else return false;
}
