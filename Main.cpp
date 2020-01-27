#include <SFML/Graphics.hpp>
#include "settings.h"
#include "car.h"

int main()
{
	Settings setting;
	sf::Vector2i windowSize = setting.getWindowSize();

	sf::RenderWindow window(sf::VideoMode(windowSize.x,windowSize.y), "CarAvoid");
	window.setFramerateLimit(60);

	Car car(5);
	int dir[2];
	car.setTexture();
	car.setSprite();
	car.saveSettings(windowSize);
	
	int size = 50;
	sf::CircleShape shape(size);
	shape.setOrigin(size,size);
	shape.setPosition(windowSize.x / 2, windowSize.y / 2);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir[0] = 1;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir[0] = -1;
			else dir[0] = 0;
		}

		car.moveCar(dir, windowSize);

		window.clear(sf::Color::Red);
		window.draw(shape);
		window.draw(car.getSprite());
		window.display();
	}

	return 0;
}