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

/*!
 * @brief Main class of the game.
 * 
 * This class contains all the logic for 
 * the actual engine of the game. This is
 * currently a candidate for heavy refactoring
 * since this class is currently handling way more than
 * I believe it should.
 * 
 */
class Game {
public:
	/*!
	 * @brief      Constructs the game object.
	 * This constructor instantiates the game's attributes, 
	 * including initializing the main window.
	 */
	Game();
	/*!
	 * @brief      Runs the game loop.
	 * 
	 * This is the main method to call after instantiating
	 * the game object, because it is what will start running the game.
	 * It contains the main game loop.
	 */
	void run();

private:
	
	// Main game loop functions
	void processEvents();	
	void update();
	void render();

	// Main game logic functions
	bool check();
	void move();
	void rotatePiece();
	void tick();
	void checkLines();
	void checkScores();
	void processText();
	void generatePiece();


	// Functions called by the constructor
	void loadAssets();
	void setupMusic();
	void setupSounds();
	void setupImages();

	

private:
	Tetris::Piece currentPiece;
	bool rotate, paused;
	int dx, dy;
	float timer, delay;
	unsigned score;
	Tetris::Board board;
	std::vector<Tetris::Point>a, b;

	// TODO: MOVE THIS SHIT AWAY FROM THIS CLASS:
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

