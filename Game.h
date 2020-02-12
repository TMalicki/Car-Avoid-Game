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

class Game 
{
	private:
		sf::RenderWindow* window;	
		sf::Event event;			

		Settings setting;
		sf::Vector2i windowSize;

		Player* car;
		vector<Traffic*> traffic;
		vector<Road> road;

		float dt; // 0.0016; // for 60 Hz
		sf::Clock clock;
		float spawnTime = 0.0; /// spawning timer of traffic cars
	public:
		Game(int i = 6); /// "i" is for amount of stripes on the road
		void setup();
		bool run();
		void draw();
		void pointsGather();
		void updateEvents(sf::RenderWindow*, sf::Event&);
		// update();
};

#endif