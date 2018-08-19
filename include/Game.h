#pragma once 

#include "Tetris.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

class Game {
public:
	Game();
	void run();

private:
	// basic game loop methods
	void processEvents();
	void update(sf::Time delta);
	void render();

	// tetris-logic related methods
	bool check();
private:
	Tetris::Board board;
	std::vector<Tetris::Point>a, b;

	sf::RenderWindow window;

};

