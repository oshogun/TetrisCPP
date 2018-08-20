#include "Game.h"

Game::Game():board(20, 10),
			 a(4), b(4),
			 rotate(false),
			 dx(0), dy(0),
			 timer(0.f), delay(0.8f),
			 currentPiece(1, 1),
			 window(sf::VideoMode(320,480), "Shikkakei") 
			 {
			 	background.loadFromFile("images/background.png");
			 	tileset.loadFromFile("images/tiles.png");
			 	frame.loadFromFile("images/frame.png");
			 }

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
		if (event.type == sf::Event::KeyPressed)
			if(event.key.code == sf::Keyboard::Up)
				rotate = true;
			else if (event.key.code == sf::Keyboard::Left)
				dx = -1;
			else if (event.key.code == sf::Keyboard::Right)
				dx = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
			delay = 0.03;
	}
}

void Game::update(sf::Time & delta)
{
	move();
	rotatePiece();
	tick(delta);
	checkLines();
}

void Game::move()
{
	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].x += dx;
	}

	if (!check()) {
		for (int i = 0; i < 4; i++) {
			a[i] = b[i];
		}
	}
}

void Game::rotatePiece()
{
	Tetris::Point p = a[1]; // center of rotation

	for (int i = 0; i < 4; i++) 
	{
		int x = a[i].y-p.y;
		int y = a[i].x-p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}

	if (!check()) {
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
	}
}

void Game::tick(sf::Time & delta)
{
	if (delta.asSeconds() > delay) {
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				board.getField()[b[i].y][b[i].x] = currentPiece.getColor();
			}

			currentPiece = Tetris::Piece(std::rand() % 7, 1 + std::rand() % 7);
			for (int i = 0; i < 4; i++)
			{
				a[i].x = currentPiece.getFigure()[i] % 2;
				a[i].y = currentPiece.getFigure()[i] / 2;
			}
		}
	}
}

bool Game::check()
{
	std::vector<std::vector<int>> field = board.getField();
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 ||
		 a[i].x >= board.getCollumns() || 
		 a[i].y >= board.getLines())
			return false;
		else if (field[a[i].y][a[i].x])
			return false;
	}
	return true;
}

void Game::checkLines()
{
	int M = board.getLines();
	int N = board.getCollumns();
	int k = M - 1;

	for (int i = M - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++ ) {
			if (board.getField()[i][j])
				count++;
		}
		if (count < N)
			k--;
	}
}
void Game::render()
{
	int M = board.getLines();
	int N = board.getCollumns();
	std::vector<std::vector<int>> field = board.getField();
	sf::Sprite s;
	window.clear();
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			if (field[i][j])
				continue;
			s.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
			s.setPosition(j * 18, i * 18);
			s.move(28, 31); // offset
			window.draw(s);
		}

	for (int i = 0; i < 4; i++) {
		s.setTextureRect(sf::IntRect(currentPiece.getColor() * 18, 0, 18, 18));
		s.setPosition(a[i].x * 18, a[i].y * 18);
		s.move(28,31); //offset
		window.draw(s);
	}
	window.display();
}