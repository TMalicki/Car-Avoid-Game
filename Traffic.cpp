#include "Traffic.h"
/*
bool Traffic::collision(Traffic& newCar, Traffic& oldCar)
{
	if (newCar.getSprite().getGlobalBounds().intersects(oldCar.getSprite().getGlobalBounds())) return true;
	else return false;
}
*/

Traffic::Traffic(float sX, float sY) : Car(sX, sY)
{
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

void Traffic::startPoint(/*std::vector<Traffic>& traffic*/sf::Vector2i windowSize, int carCorrection)
{
	int line = std::rand() % 5 + 0;
	bool flag = false;

	int temp = line;
	//int size = traffic.size();
	/// collision !!!
	//while (collision(traffic[size - 1], traffic[size - 2]) && flag = false) /// zle, musza byc patrzone wszystkie pojazdy a nie tylko ostatnie dwa
	//{
	//	line += 1;
	//	if (line > 5) line = 0;
	//}

	sCar.rotate(180.0);
	sCar.setPosition(50 + 100*line, -carCorrection);
}

void Traffic::moveCar(sf::Vector2i windowSize, float dt)
{
	sCar.move(0, dt * timeMultiply * speed.y);
}
