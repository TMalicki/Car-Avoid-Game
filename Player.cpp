#include "Player.h"
#include <string>

int Player::lvl = 0;

Player::Player(float sX, float sY) : Car(sX, sY), score(0) {
	font.loadFromFile("fonts/QuiteMagical.ttf");

	tScore.setFont(font);
	tScore.setCharacterSize(20);
	tScore.setFillColor(sf::Color::White);
	tScore.setPosition(10, 10);
}

void Player::setText()
{
	std::string temp = "Points: " + std::to_string(score);
	tScore.setString(temp);
}

void Player::startPoint(sf::Vector2i windowSize, int carCorrection)
{
	sCar.setPosition(windowSize.x / 2, windowSize.y - carCorrection);
	calculateCollisionArea();
}

void Player::moveCar(sf::Vector2i windowSize, float dt)
{
	static int counter = 0;
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

	/* -------------------------------------------   */
	counter++;
	if (counter == 50) {
	counter = 0;
	/* -------------------------------------------   */
	}

	calculateCollisionArea();
	bullet.move(windowSize, dt);
}

void Player::calculateCollisionArea()
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
	
	sf::Vertex points[5] = { topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, topLeftCorner };
	
	collisionArea = new sf::VertexArray(sf::LineStrip, 5);
	
	for (int i = 0; i < 5; i++) {
		///(*collisionArea)[i].texCoords = points[i].position;
		(*collisionArea)[i].position = points[i].position;
	}
	
	//std::cout << bottomRightCorner.y << " " << topRightCorner.y << std::endl;
	//std::cout << (bottomRightCorner.y - topRightCorner.y) / ((topRightCorner.x - bottomRightCorner.x)) << std::endl;
}

void Player::lvlUp(std::vector<Car*> trafficCar)
{
	if (score % 10 == 0) {
		lvl++; 
	}
}

bool Player::collision(std::vector<Car*> trafficCar)
{
	bool state = 0;
	int size = trafficCar.size();
	
	float angleHorizontalRight = (bottomRightCorner.y - topRightCorner.y) / ((topRightCorner.x - bottomRightCorner.x));
	float bHorizontalRight = (topRightCorner.y * bottomRightCorner.x - bottomRightCorner.y * topRightCorner.x) / (bottomRightCorner.x - topRightCorner.x);

	while (size-- && state == false)

		//float xTemp = trafficCar[size]->getSprite().getGlobalBounds().left;
		//float yTemp = angleHorizontalRight * xTemp;

		if (trafficCar[size]->getSprite().getGlobalBounds().contains(topRightCorner)) return true;
		//if (this->getSprite().getGlobalBounds().intersects(trafficCar[size]->getSprite().getGlobalBounds())) return true;
}

void Player::pointsGather(std::vector<Car*>& trafficCar, sf::Vector2i windowSize)
{
	if ((*trafficCar.begin())->getSprite().getGlobalBounds().top >= windowSize.y)
	{
		score++;
		trafficCar.erase(trafficCar.begin());
		lvlUp(trafficCar);
	}
}

void Player::shoot()
{
	sf::FloatRect bounds = sCar.getGlobalBounds();
	float mid = (bounds.left + bounds.width / 2);
	bullet.position(mid, bounds.top);
}
