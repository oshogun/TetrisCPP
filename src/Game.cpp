#include "Game.h"

Game::Game():board(20, 10),
			 a(4),
			 b(4),
			 window(sf::VideoMode(320,480), "Dogoo's Tetrimino Puzzle") 
			 {}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > sf::seconds (1.f /60.f)) {
			timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
			processEvents();
			update(timeSinceLastUpdate);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while(window.pollEvent(event)) {
		if (event.type == sf::Event::Closed){
			window.close();
		}
	}
}
void Game::update(sf::Time delta){}

void Game::render()
{
	window.clear();
	window.display();
}