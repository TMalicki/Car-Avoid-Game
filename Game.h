#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "settings.h"
#include "car.h"
#include "Road.h"
#include "Player.h"
#include "Traffic.h"
#include <vector>

class Game {
private:
	Settings setting;
	sf::RenderWindow* window;
	sf::Event event;
	sf::Vector2i windowSize;

	Car* car;
	vector<Road> road;
	vector<Traffic*> traffic;

	float dt = 0.0016;
	sf::Clock clock;
public:
	Game(int i = 6);
	void setup();
	bool run();
	void draw();
};

#endif