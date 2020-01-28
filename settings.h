#ifndef SETTINGS_H
#define SETTINGS_H
#include <iostream>

class Settings {
private:
	int globX;
	int globY;
public:
	Settings(int x = 500, int y = 800) { globX = x; globY = y; }
	void setWindowSize(int x, int y) { globX = x; globY = y; }
	sf::Vector2i getWindowSize() const { return sf::Vector2i(globX, globY); }
};



#endif SETTINGS_H