#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "settings.h"
#include "car.h"
#include "Road.h"
#include <vector>

class Game {
private:
	Settings setting;
	sf::RenderWindow* window;
	sf::Event event;
	sf::Vector2i windowSize;

	Car* car;
	vector<Road> road;
public:
	Game(int i = 6);
	void setup();
	bool run();
	void draw();
};

#endif