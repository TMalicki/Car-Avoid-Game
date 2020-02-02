#include "Game.h"

using namespace std;

Game::Game(int i) : road{1,2,3,4,5,6}
{
	setup();
	run();
	draw();
}

void Game::setup()
{
	srand(time(NULL));

	windowSize = setting.getWindowSize();

	window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "CarAvoid");
	
	car = new Player;
	car->saveSettings(windowSize);
	car->setText();

	for(int i = 0;i<road.size();i++)
		road[i].setStripPosition(&windowSize.x);
}

bool Game::run()
{
	while (window->isOpen() /*&& !car->collision(traffic)*/)
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window->close();
		}
		dt = clock.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) car->setDir(sf::Vector2i(1, 0));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) car->setDir(sf::Vector2i(-1, 0));
		else car->setDir(sf::Vector2i(0, 0));

		/*  -------------------------------------------------  */
		if (spawnTime > 2.0) {
				traffic.push_back(new Traffic{ 0.0, 9.0f + 1.0f * Player::getLvl() });
		
			traffic.back()->saveSettings(windowSize);
			spawnTime = 0.0;
		}

		spawnTime += dt +(0.0005 * Player::getLvl());

		if (traffic.size() != 0)
			for (int i = 0; i < traffic.size(); i++)
				traffic[i]->moveCar(windowSize, dt);
		/*  -------------------------------------------------  */

		car->moveCar(windowSize, dt);

		if (traffic.size() != 0) car->pointsGather(traffic, windowSize);

		car->setText();

		for(int i = 0; i < road.size();i++)
			road[i].move(windowSize, dt, Player::getLvl());

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

	window->draw(car->getText());

	window->display();
}