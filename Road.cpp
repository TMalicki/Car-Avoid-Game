#include "Road.h"

Road::Road(int sp, int s, int w, int l) : startPosition(sp), speed(s), stripWidth(w), stripLength(l), roadStrip(6)
{ 

	for (int i = 0; i < stripAmount; i++)
	{
		roadStrip[i].setSize(sf::Vector2f(stripWidth, stripLength));
		roadStrip[i].setOrigin(stripWidth / 2, stripLength / 2);
		roadStrip[i].setFillColor(sf::Color::White);
	//	roadStrip[i].setPosition(*windowSize/stripAmount * i, 200*startPosition);
	}
}

void Road::setStripPosition(int* winSize)
{
	windowSize = winSize;

	for(int i = 0;i<roadStrip.size();i++)
	roadStrip[i].setPosition(((float)*windowSize - stripWidth/2) / (stripAmount - 1) * i, 200 * startPosition);
}

void Road::move(sf::Vector2i windowSize, float dt, int lvl)
{
	for (int i = 0; i < roadStrip.size(); i++)
	{
		roadStrip[i].move(0, speed * dt * timeMultiply + 0.1 * lvl);
		sf::Vector2f position = roadStrip[i].getPosition();
		if (position.y > windowSize.y) roadStrip[i].setPosition(position.x, position.y - windowSize.y);
	}
}


