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
	windowSize = setting.getWindowSize();


	window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "CarAvoid");
	//window->setFramerateLimit(60); //  60 f/s -> 0.016 s/frame //1818
	//dt = 0.033
	
	car = new Player(windowSize);
	car->saveSettings(windowSize);

	for(int i = 0;i<road.size();i++)
		road[i].setStripPosition(&windowSize.x);
}

bool Game::run()
{
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window->close();
		}
		
		cout << dt << endl;
		dt = clock.restart().asSeconds();
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) car->setDir(sf::Vector2i(1, 0));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) car->setDir(sf::Vector2i(-1, 0));
		else car->setDir(sf::Vector2i(0, 0));

		//traffic.push_back(new Traffic(windowSize));

		car->moveCar(windowSize, dt);

		for(int i = 0; i < road.size();i++)
		road[i].move(windowSize, dt);

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
	window->draw(car->getSprite());

	window->display();
}