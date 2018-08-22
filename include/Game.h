#pragma once 

#include "Tetris.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class Game {
public:
	Game();
	void run();

private:
	// basic game loop methods
	void processEvents();
	void update();
	void render();

	// tetris-logic related methods
	bool check();

	void move();
	void rotatePiece();
	void tick();
	void checkLines();
	void checkScores();
	void processText();

	// literally all the shit the constructor calls
	void loadAssets();
	void setupMusic();
	void setupSounds();
	void setupImages();
	void generatePiece();

private:
	Tetris::Piece currentPiece;
	bool rotate, paused;
	int dx, dy;
	float timer, delay;
	unsigned score;
	Tetris::Board board;
	std::vector<Tetris::Point>a, b;

	// SFML Resources
	sf::RenderWindow window;
	sf::Texture background_t, frame_t, tileset_t;
	sf::Sprite background, frame;
	sf::Music bgm;
	sf::SoundBuffer pew_buffer;
	sf::SoundBuffer bloop_buffer;
	sf::Sound pew;
	sf::Sound bloop;
	sf::Font opensans_bold;
	sf::Text scoreboard, paused_text;
};

