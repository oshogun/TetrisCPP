#include "Game.h"

Game::Game():
	board(20, 10),	
	a(4), b(4),
	rotate(false),
	dx(0), dy(0),
	timer(0.f), delay(0.8f),
	currentPiece(1, 1),
	window(sf::VideoMode(320,480), "Tetris da KURISUTINA",sf::Style::Titlebar) 
	{
		if (!bgm.openFromFile("music/elpsykongroo.wav")) {
			throw std::runtime_error("Failed to load music/elpsykongroo.wav");
		}
		if (!pew_buffer.loadFromFile("soundfx/beep-02.wav")) {
			throw std::runtime_error("Failed to load soundfx/beep-02.wav");
		}
		bgm.setLoop(true);
		bgm.setVolume(25);
		bgm.play();
		pew.setBuffer(pew_buffer);
		pew.setVolume(50);
		background_t.loadFromFile("images/background.png");
		tileset_t.loadFromFile("images/tiles.png");
		frame_t.loadFromFile("images/frame.png");
		background = sf::Sprite(background_t);
		frame = sf::Sprite(frame_t);
		for (int i = 0; i < 4; i++)
		{
			a[i].x = currentPiece.getFigure()[i] % 2;
			a[i].y = currentPiece.getFigure()[i] / 2;
		}
	}

void Game::run()
{
	srand(time(NULL));
	sf::Clock clock;	
	while(window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		
		processEvents();

		update();
		dx = 0; 
		rotate = false; 
		delay = 0.3;
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
		if (event.type == sf::Event::KeyPressed) {
			pew.play();
			if(event.key.code == sf::Keyboard::Up)
				rotate = true;
			else if (event.key.code == sf::Keyboard::Left)
				dx = -1; 
			else if (event.key.code == sf::Keyboard::Right)
				dx = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
			delay = 0.01;
	}
}

void Game::update()
{
	move();
	if (rotate && currentPiece.getType() != 6);
		rotatePiece();
	tick();
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
	if (rotate && currentPiece.getType() != 6) {
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
}

void Game::tick()
{
	if (timer > delay) {
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
		timer = 0;
	}
}

bool Game::check()
{
	std::vector<std::vector<int>> field = board.getField();
	int M = board.getLines();
	int N = board.getCollumns();
	for (int i=0;i<4;i++)
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) { 
      	  return 0;
      }

   return 1;
}

void Game::checkLines()
{
	int M = board.getLines();
	int N = board.getCollumns();
	std::vector<std::vector<int>> field = board.getField();
	int k = M - 1;

	for (int i = M - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++ ) {
			if (field[i][j])
				count++;
			board.getField()[k][j] = board.getField()[i][j];
			
		}
		if (count < N) {
			k--;			
		}
	}

}
void Game::render()
{
	int M = board.getLines();
	int N = board.getCollumns();
	std::vector<std::vector<int>> field = board.getField();
	sf::Sprite s(tileset_t);
	window.clear();
	window.draw(background);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			if (field[i][j] == 0)
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
	window.draw(frame);
	window.display();
}