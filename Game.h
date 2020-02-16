#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

		sf::Sprite sEndScreen;
		sf::Texture tEndScreen;
		sf::Sprite sChooseBar;
		sf::Texture tChooseBar;

		sf::Texture tExplosion;
		sf::Sprite sExplosion;
		sf::IntRect rectSourceSprite;
		int explosionCounter = 0;
		float timeExplosion = 0.0;

		sf::SoundBuffer bShot;
		sf::Sound sShot;

		float dt; // 0.0016; // for 60 Hz
		sf::Clock clock;
		float spawnTime = 0.0; /// spawning timer of traffic cars
		bool theEnd = false;
	public:
		Game(int i = 6); /// "i" is for amount of stripes on the road
		void setup();
		bool run();
		void draw();
		void pointsGather();
		void updateEvents(sf::RenderWindow*, sf::Event&);
		void updateVehicles();
		void bulletMove();
		// update();
};

#endif