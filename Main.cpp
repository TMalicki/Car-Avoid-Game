#include <SFML/Graphics.hpp>
#include "Game.h"

/// remake everything that works with frame to dt depending
/// make traffic cars generating paralelly
int main()
{
	Game* game = new Game;
	game->run();

	return 0;
}

/// do poprawy - podczas reloadingu jest sie odpornym na kolizje
/// ograniczyc trzeba poziomy zdobywane