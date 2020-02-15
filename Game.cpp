#include "Game.h"

using namespace std;

Game::Game(int i) : road{1,2,3,4,5,6}
{
	setup();
}

void Game::setup()
{
	srand(time(NULL));

	windowSize = setting.getWindowSize();
	window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "CarAvoid");
	
	car = new Player;
	car->saveSpriteSettings(windowSize);
	car->calculateSpriteVertexes();
	car->setText();

	for (int i = 0; i < road.size(); i++)
	{
		road[i].setStripPosition(&windowSize.x);
	}

	tEndScreen.loadFromFile("sprites/gameover.png");
	tChooseBar.loadFromFile("sprites/chooseBar.png");

	sEndScreen.setTexture(tEndScreen);
	sEndScreen.setScale(0.7, 0.7);
	sEndScreen.setPosition(25, 100);

	sChooseBar.setTexture(tChooseBar);
	sChooseBar.setColor(sf::Color(255, 255, 255, 128));
	sChooseBar.setScale(0.7, 0.7);
	sChooseBar.setPosition(178, 462);
}

bool Game::run()
{
	while (window->isOpen() && !car->collisionSAT(traffic))
	{
		updateEvents(window, event);

		if (theEnd == false)
		{
		dt = clock.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) car->setDir(sf::Vector2i(1, 0));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) car->setDir(sf::Vector2i(-1, 0));
		else car->setDir(sf::Vector2i(0, 0));

		if (Bullet::Recoil())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				car->shoot();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && car->getReloading() == false) car->setReloading(true);

		if (car->getReloading() == true) car->reload(dt);

		if (spawnTime > 2.0)
		{
			traffic.push_back(new Traffic{ 0.0, 9.0f + 1.0f * Player::getLvl() });
			traffic.back()->saveSpriteSettings(windowSize);
			spawnTime = 0.0;
		}

		spawnTime += dt + (0.0005 * Player::getLvl());

		if (traffic.size() != 0)
			for (int i = 0; i < traffic.size(); i++)
				traffic[i]->moveCar(windowSize, dt);
		/*  -------------------------------------------------  */

		car->moveCar(windowSize, dt);
		car->calculateSpriteVertexes();
		car->showCollisionArea();
		//bulletMove();
		car->bulletMove(windowSize, dt);	// to nie powinno byc w klasie bullet?

		if (traffic.size() != 0) pointsGather();

		car->setText();

		for (int i = 0; i < road.size(); i++)
			road[i].move(windowSize, dt, Player::getLvl());
		}
		else if (theEnd == true)
		{

		}
		draw();
	}
	return true;
}

void Game::draw()
{
	window->clear(sf::Color(100,100,100,0));

	for (int j = 0; j < road.size(); j++)
	{
		for (int i = 0; i < road[j].getSize(); i++)
		{
			window->draw(road[j].getRoad(i));
		}
	}
	/*  -------------------------------------------------  */
	if (traffic.size() != 0)
		for(int i = 0; i < traffic.size(); i++)
			window->draw(traffic[i]->getSprite());
	/*  -------------------------------------------------  */
	window->draw(car->getSprite());
	window->draw(car->getCollisionArea());

	if (car->getBulletSize() != 0) {
		for (int i = 0; i < car->getBulletSize(); i++) {
			window->draw(car->getBulletSprite(i));
		}
	}

	window->draw(car->getText());
	window->draw(car->getMagazine());

	if (theEnd == true)
	{
		window->draw(sEndScreen);
		window->draw(sChooseBar);
	}
	window->display();
}


void Game::pointsGather()
{
	if ((*traffic.begin())->getSprite().getGlobalBounds().top >= windowSize.y)
	{
		car->scoreUp();
		traffic.erase(traffic.begin());
		car->lvlUp();
	}

	for (int i = 0; i < traffic.size() && traffic.size() != 0; i++)
	{
		if (traffic[i]->collision(car->getBulletVect()))
		{ 
			car->scoreUp();
			traffic.erase(traffic.begin() + i);
			car->lvlUp();
		}
	}
}

void Game::updateEvents(sf::RenderWindow* window, sf::Event& event)
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				theEnd = true;
			}
		}	
		if (theEnd == true)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (sChooseBar.getPosition().x == 178)
					{
						theEnd = false;
						setup();
					}
					else if (sChooseBar.getPosition().x == 284) window->close();
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					sChooseBar.setPosition(284, 462);
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					sChooseBar.setPosition(178, 462);
				}
			}
		}
	}
}
/*
void Game::bulletMove()
{
	int bulletSize = car->getBulletSize();
	if (bulletSize != 0)
	{
		for (int i = 0; i < bulletSize; i++)
		{
			car->getBulletObj(i).move(windowSize, dt);
			//bullet[i].move(windowSize, dt);
			if (car->getBulletVect().back().getPosition() < 0)
			{
				car->getBulletVect().pop_back();
			}
		}
	}
}
*/