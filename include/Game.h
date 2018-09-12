#pragma once 

#include "Tetris.h"
#include "AssetHolder.hpp"
#include "Assets.h"
#include "MusicHandler.h"
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
 * I believe it should, thus making it a fine example
 * of the God Object Design Anti-Pattern.
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
	void processScoreboard();
	void processPausedText();
	void processPieceCountText();
	void generatePiece();
	void resetGame();

	// Functions called by the constructor
	void loadAssets();
	void setupMusic();
	void setupSounds();
	void setupImages();

	

private:
	Tetris::Piece currentPiece;
	bool rotate, paused, running, gameOver;
	int dx, totalClearedLines, linesToNextLevel, level;
	float timer, delay, normaldelay;
	unsigned score;
	Tetris::Board board;
	std::array<Tetris::Point, 4>a, b;
	std::array<int,7> pieceCount;

	AssetHolder<sf::Texture, Assets> textureHolder;
	AssetHolder<sf::Font, Assets> fontHolder;
	AssetHolder<sf::SoundBuffer, Assets> soundBufferHolder;
	
	sf::RenderWindow window;
	sf::Music bgm;
	MusicHandler musicHandler;
	sf::Sound bloop, pew;
	sf::Text scoreboard, paused_text, instructions, pieceCountText;

};

