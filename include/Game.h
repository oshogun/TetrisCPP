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
	void update(sf::Time & delta);
	void render();

	// tetris-logic related methods
	bool check();

	void move();
	void rotatePiece();
	void tick(sf::Time & delta);
	void checkLines();

private:
	Tetris::Piece currentPiece;
	bool rotate;
	int dx, dy;
	float timer, delay;
	Tetris::Board board;
	std::vector<Tetris::Point>a, b;

	sf::RenderWindow window;
	sf::Texture background, frame, tileset;

};

