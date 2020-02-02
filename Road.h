#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;
class Road {
private:
	vector<sf::RectangleShape> roadStrip;
	int stripWidth;
	int stripLength;
	int speed;
	int stripAmount = 6;
	float startPosition;
	int* windowSize;
	float timeMultiply = 62.5;
public:
	Road(int sp = 0, int s = 10, int w = 5, int l = 50);
	
	void setStripPosition(int* winSize);
	sf::RectangleShape getRoad(int i) { return roadStrip[i]; }
	int getSize() { return roadStrip.size(); }
	void move(sf::Vector2i, float, int);
};


#endif
