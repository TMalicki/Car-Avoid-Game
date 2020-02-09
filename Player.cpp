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

	if (bullet.size() != 0)
	{
		for (int i = 0; i < bullet.size(); i++) {
			bullet[i].move(windowSize, dt);
			if (bullet.back().getPosition() < 0) bullet.pop_back();
		}
	}

	//magazine.move(10, 10);
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
		(*collisionArea)[i].position = points[i].position;
	}
}

bool Player::collision(std::vector<Car*> trafficCar)
{
	if (trafficCar.size() != 0) return collisionSAT(trafficCar.front());
	else return false;
}

bool Player::collisionSAT(Car* traffic)
{
	bool collided = true;
	int counter = 1;
	/// vertexes of player object are: A - topLeftCorner, B - topRightCorner, C - bottomRightCorner, D - bottomLeftCorner (clockwise)
	/// vertexes od traffic Car object are: E, F, G, H (clockwise)

	sf::FloatRect trafficCar = traffic->getSprite().getGlobalBounds();
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

	sf::Vector2f normVector;

	float projectionVertexABCD[4];
	float projectionVertexEFGH[4];

	float playerMin;
	float playerMax;
	float trafficMin;
	float trafficMax;

	using namespace std;

	while (collided == true && counter <= 4)
	{
		/// for normVectorABplayer
		if (counter == 1) normVector = normVectorABplayer;
		/// for normVectorBCplayer
		else if (counter == 2) normVector = normVectorBCplayer;
		/// for normVectorEFtraffic
		else if (counter == 3) normVector = normVectorEFtraffic;
		/// for normVectorGHtraffic
		else if (counter == 4) normVector = normVectorGHtraffic;

		projectionVertexABCD[0] = normVector.x * topLeftCorner.x + normVector.y * topLeftCorner.y;
		projectionVertexABCD[1] = normVector.x * topRightCorner.x + normVector.y * topRightCorner.y;
		projectionVertexABCD[2] = normVector.x * bottomRightCorner.x + normVector.y * bottomRightCorner.y;
		projectionVertexABCD[3] = normVector.x * bottomLeftCorner.x + normVector.y * bottomLeftCorner.y;

		playerMin = projectionVertexABCD[0];
		playerMax = projectionVertexABCD[0];
		for (int i = 1; i < 4; i++) 
		{
			if (playerMin > projectionVertexABCD[i]) playerMin = projectionVertexABCD[i];
			if (playerMax < projectionVertexABCD[i]) playerMax = projectionVertexABCD[i];
		}

		projectionVertexEFGH[0] = normVector.x * trafficTopLeftCorner.x + normVector.y * trafficTopLeftCorner.y;
		projectionVertexEFGH[1] = normVector.x * trafficTopRightCorner.x + normVector.y * trafficTopRightCorner.y;
		projectionVertexEFGH[2] = normVector.x * trafficBottomRightCorner.x + normVector.y * trafficBottomRightCorner.y;
		projectionVertexEFGH[3] = normVector.x * trafficBottomLeftCorner.x + normVector.y * trafficBottomLeftCorner.y;

		trafficMin = projectionVertexEFGH[0];
		trafficMax = projectionVertexEFGH[0];
		for (int i = 1; i < 4; i++) 
		{
			if (trafficMin > projectionVertexEFGH[i]) trafficMin = projectionVertexEFGH[i];
			if (trafficMax < projectionVertexEFGH[i]) trafficMax = projectionVertexEFGH[i];
		}

		/// negation
		if (!(((playerMin < trafficMax) && (playerMin > trafficMin)) || ((trafficMin < playerMax) && (trafficMin > playerMin))))
		{
			collided = false;
		}
		counter++;

		cout << "Counter: " << counter << endl;
		cout << " topLeftCorner: X: " << topLeftCorner.x << " Y: " << topLeftCorner.y << endl;
		cout << " bottomLeftCorner: X: " << bottomLeftCorner.x << " Y: " << bottomLeftCorner.y << endl;
		cout << " trafficTopLeftCorner: X: " << trafficTopLeftCorner.x << " Y: " << trafficTopLeftCorner.y << endl;
		cout << " trafficBottomLeftCorner: X: " << trafficBottomLeftCorner.x << " Y: " << trafficBottomLeftCorner.y << endl;
	}
	return collided;
}

void Player::lvlUp(std::vector<Car*> trafficCar)
{
	if (score % 10 == 0) {
		lvl++;
	}
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

void Player::shoot(sf::Vector2i windowSize, float dt)
{
	//if (Bullet::getRecoil() <= timeToShoot)
	//{
		Bullet temp;
		sf::FloatRect bounds = sCar.getGlobalBounds();
		float mid = (bounds.left + bounds.width / 2);

		if (bulletAmount < bulletMaxAmount) {
			if (bulletAmount > 0)
			{
				if (bullet.back().Recoil())
				{
					bullet.push_back(temp);
					bulletAmount++;
					bullet.back().position(mid, bounds.top);
				}
			}
			else
			{
				bullet.push_back(temp);
				bulletAmount++;
				bullet.back().position(mid, bounds.top);
			}
		}
		else if (bulletAmount == bulletMaxAmount) reload();
}

void Player::reload()
{
	static int counter = 0;

	if (counter >= 800)
	{
		bulletAmount = 0;
		counter = 0;
	}
	counter++;
}
