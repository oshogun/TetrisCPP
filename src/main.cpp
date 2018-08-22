#include "Tetris.h"
#include "Game.h"
#include <iostream>

int main()
{
	std::srand(time(NULL));
	Game game;
	game.run();
}