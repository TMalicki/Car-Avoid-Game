#include "Player.h"
#include <string>

int Player::lvl = 0;

Player::Player(float sX, float sY) : Car(sX, sY), score(0) 
{
	font.loadFromFile("fonts/QuiteMagical.ttf");

	tScore.setFont(font);
	tScore.setCharacterSize(20);
	tScore.setFillColor(sf::Color::White);
	tScore.setPosition(10, 10);

	magazine.setFillColor(sf::Color::White);
	magazine.setRadius(10);
	magazine.setOrigin(2, 2);

	sf::Vector2f tempPos = sCar.getPosition();

	magazine.setPosition(tempPos.x + 5,600);
}

void Player::setText()
{
	std::string temp = "Points: " + std::to_string(score);
	tScore.setString(temp);
}

void Player::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	sCar.setPosition(windowSize.x / 2, windowSize.y - carCorrection);
}

void Player::moveCar(sf::Vector2i windowSize, float dt)
{
	if (dir.x == 1)
	{
		sCar.setRotation(10);
		if (sCar.getPosition().x + (sCar.getGlobalBounds().width / 2) < windowSize.x) sCar.move(speed.x * dt * timeMultiply, 0.0);
	}
	else if (dir.x == -1)
	{
		sCar.setRotation(-10);
		if (sCar.getPosition().x - (sCar.getGlobalBounds().width / 2) > 0) sCar.move(-speed.x * dt * timeMultiply, 0.0);
	}
	else if (dir.x == 0) sCar.setRotation(0);
}

void Player::calculateSpriteVertexes()
{
	sf::Sprite playerSprite = this->getSprite();
	sf::Transform playerSpriteTransformed = playerSprite.getTransform();
	sf::FloatRect playerLocalBounds = playerSprite.getLocalBounds();
	
	topLeftCorner = playerSpriteTransformed.transformPoint(sf::Vector2f(playerLocalBounds.left, playerLocalBounds.top));
	topRightCorner = playerSpriteTransformed.transformPoint(sf::Vector2f(playerLocalBounds.left + playerLocalBounds.width, playerLocalBounds.top));
	bottomRightCorner = playerSpriteTransformed.transformPoint(sf::Vector2f(playerLocalBounds.left + playerLocalBounds.width
		, playerLocalBounds.top + playerLocalBounds.height));
	bottomLeftCorner = playerSpriteTransformed.transformPoint(sf::Vector2f(playerLocalBounds.left, playerLocalBounds.top
		+ playerLocalBounds.height));
}

void Player::showCollisionArea()
{
	sf::Vertex points[5] = { topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, topLeftCorner };

	collisionArea = new sf::VertexArray(sf::LineStrip, 5);

	for (int i = 0; i < 5; i++) 
	{
		(*collisionArea)[i].position = points[i].position;
	}
}

bool Player::collisionSAT(std::vector<Traffic*> traffic)
{
	bool collided = true;
	int counter = 1;
	/// vertexes of player object are: A - topLeftCorner, B - topRightCorner, C - bottomRightCorner, D - bottomLeftCorner (clockwise)
	/// vertexes od traffic Car object are: E, F, G, H (clockwise)

	if (traffic.size() != 0)
	{
		sf::FloatRect trafficCar = traffic.front()->getSprite().getGlobalBounds();	/// is it necessary to check if it;s not front() sprite? try that!
		sf::Vector2f trafficTopLeftCorner = sf::Vector2f(trafficCar.left, trafficCar.top);
		sf::Vector2f trafficTopRightCorner = sf::Vector2f(trafficCar.left + trafficCar.width, trafficCar.top);
		sf::Vector2f trafficBottomRightCorner = sf::Vector2f(trafficCar.left + trafficCar.width, trafficCar.top + trafficCar.height);
		sf::Vector2f trafficBottomLeftCorner = sf::Vector2f(trafficCar.left, trafficCar.top + trafficCar.height);

		sf::Vector2f vectorABplayer = sf::Vector2f(topRightCorner.x - topLeftCorner.x, topRightCorner.y - topLeftCorner.y);
		sf::Vector2f vectorBCplayer = sf::Vector2f(bottomRightCorner.x - topRightCorner.x, bottomRightCorner.y - topRightCorner.y);
		sf::Vector2f vectorEFtraffic = sf::Vector2f(trafficTopRightCorner.x - trafficTopLeftCorner.x, trafficTopRightCorner.y - trafficTopLeftCorner.y);
		sf::Vector2f vectorGHtraffic = sf::Vector2f(trafficBottomRightCorner.x - trafficTopRightCorner.x, trafficBottomRightCorner.y - trafficTopRightCorner.y);

		sf::Vector2f normVectorABplayer = sf::Vector2f(-vectorABplayer.y, vectorABplayer.x);
		sf::Vector2f normVectorBCplayer = sf::Vector2f(-vectorBCplayer.y, vectorBCplayer.x);
		sf::Vector2f normVectorEFtraffic = sf::Vector2f(-vectorEFtraffic.y, vectorEFtraffic.x);
		sf::Vector2f normVectorGHtraffic = sf::Vector2f(-vectorGHtraffic.y, vectorGHtraffic.x);

		sf::Vector2f normVectorActual;

		float projectionPlayerVertex[4];
		float projectionTrafficVertex[4];

		float playerMin;
		float playerMax;
		float trafficMin;
		float trafficMax;

		while (collided == true && counter <= 4)
		{
			/// checking all significant vectors (projections) 
			if (counter == 1) normVectorActual = normVectorABplayer;
			else if (counter == 2) normVectorActual = normVectorBCplayer;
			else if (counter == 3) normVectorActual = normVectorEFtraffic;
			else if (counter == 4) normVectorActual = normVectorGHtraffic;

			projectionPlayerVertex[0] = normVectorActual.x * topLeftCorner.x + normVectorActual.y * topLeftCorner.y;
			projectionPlayerVertex[1] = normVectorActual.x * topRightCorner.x + normVectorActual.y * topRightCorner.y;
			projectionPlayerVertex[2] = normVectorActual.x * bottomRightCorner.x + normVectorActual.y * bottomRightCorner.y;
			projectionPlayerVertex[3] = normVectorActual.x * bottomLeftCorner.x + normVectorActual.y * bottomLeftCorner.y;

			playerMin = projectionPlayerVertex[0];
			playerMax = projectionPlayerVertex[0];
			for (int i = 1; i < 4; i++)
			{
				if (playerMin > projectionPlayerVertex[i]) playerMin = projectionPlayerVertex[i];
				if (playerMax < projectionPlayerVertex[i]) playerMax = projectionPlayerVertex[i];
			}

			projectionTrafficVertex[0] = normVectorActual.x * trafficTopLeftCorner.x + normVectorActual.y * trafficTopLeftCorner.y;
			projectionTrafficVertex[1] = normVectorActual.x * trafficTopRightCorner.x + normVectorActual.y * trafficTopRightCorner.y;
			projectionTrafficVertex[2] = normVectorActual.x * trafficBottomRightCorner.x + normVectorActual.y * trafficBottomRightCorner.y;
			projectionTrafficVertex[3] = normVectorActual.x * trafficBottomLeftCorner.x + normVectorActual.y * trafficBottomLeftCorner.y;

			trafficMin = projectionTrafficVertex[0];
			trafficMax = projectionTrafficVertex[0];
			for (int i = 1; i < 4; i++)
			{
				if (trafficMin > projectionTrafficVertex[i]) trafficMin = projectionTrafficVertex[i];
				if (trafficMax < projectionTrafficVertex[i]) trafficMax = projectionTrafficVertex[i];
			}

			/// negation
			if (!(((playerMin < trafficMax) && (playerMin > trafficMin)) || ((trafficMin < playerMax) && (trafficMin > playerMin))))
			{
				collided = false;
			}
			counter++;
		}
	}
	else collided = false;

	return collided;
}

void Player::lvlUp()
{
	if (score % 10 == 0) {
		lvl++;
	}
}

void Player::shoot()
{
	if (getReloading() == false)
	{
		Bullet temp;
		sf::Vector2f bulletPos{ (topLeftCorner.x + topRightCorner.x) / 2, (topLeftCorner.y + topRightCorner.y) / 2 };

		if (bulletAmount < bulletMaxAmount)
		{
			if (bulletAmount > 0)
			{
				bullet.push_back(temp);
				bulletAmount++;
				bullet.back().position(bulletPos.x, bulletPos.y);
			}
			else
			{
				bullet.push_back(temp);
				bulletAmount++;
				bullet.back().position(bulletPos.x, bulletPos.y);
			}
			Bullet::setTimeToRecoil(0.0);
		}
	}
}

void Player::reload(float dt)
{
	static float counter = 0.0;

	if (counter >= 1.5)
	{
		bulletAmount = 0;
		counter = 0.0;
		setReloading(false);
	}
	counter+=dt;
	std::cout << counter << std::endl;
}

void Player::bulletMove(sf::Vector2i windowSize, float dt)
{
	if (bullet.size() != 0)
	{
		for (int i = 0; i < bullet.size(); i++)
		{
			bullet[i].move(windowSize, dt);
			if (bullet.back().getPosition() < 0)
			{
				bullet.pop_back();
			}
		}
	}
}
