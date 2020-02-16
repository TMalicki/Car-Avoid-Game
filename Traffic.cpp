#include "Traffic.h"

Traffic::Traffic(float sX, float sY) : Car(sX, sY)
{
}

bool Traffic::collision(vector<Traffic*>& traffic)
{
	bool state = false;
	sf::FloatRect actualTrafficCar = this->getSprite().getGlobalBounds();

	for (int i = 0; i < traffic.size() && state == false; i++)
	{
		if (actualTrafficCar.intersects(traffic[i]->getSprite().getGlobalBounds())) state = true;
	}

	return state;
}

bool Traffic::collision(vector<Bullet>& bullet)
{
	int tempSize = bullet.size();
	int tempLogic = false;

	while(tempSize-- && tempLogic == false)
	{
		if (this->getSprite().getGlobalBounds().intersects(bullet[tempSize].getBullet().getGlobalBounds()))
		{
			tempLogic = true;
			bullet.erase(bullet.begin() + tempSize);
		}
	}

	return tempLogic;
}

void Traffic::changeLine(int line)
{
	sCar.move(100 * line, 0);
}

void Traffic::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	int line = std::rand() % 5 + 0;

	sCar.rotate(180.0);
	sCar.setPosition(50 + 100*line, -carCorrection);
}

void Traffic::moveCar(sf::Vector2i windowSize, float dt)
{
	sCar.move(0, dt * timeMultiply * speed.y);
}
