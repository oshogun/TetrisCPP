#include "Game.h"

Game::Game():	
	rotate(false),
	dx(0),
	timer(0.f), delay(0.8f), normaldelay(0.8f),
	currentPiece(1, 1),
	score(0),
	paused(false),
	level(1),
	totalClearedLines(0),
	linesToNextLevel(0),
	window(sf::VideoMode(640,480), "Tetris C++17 (Name Subject to Change)",sf::Style::Close) 
	{	
		loadAssets();
		setupMusic();
		setupSounds();
		generatePiece();		
	}

void Game::loadAssets()
{
	fontHolder.loadAssetFromFile(font_opensans_bold, "fonts/OpenSans-Bold.ttf");	
	if (!bgm.openFromFile("music/borb.wav")) {
		throw std::runtime_error("Failed to load music/borb.wav");
	}
	soundBufferHolder.loadAssetFromFile(soundBuffer_pew_buffer, "soundfx/pew.wav");	
	soundBufferHolder.loadAssetFromFile(soundBuffer_bloop_buffer, "soundfx/beep-02.wav");	
	textureHolder.loadAssetFromFile(background_texture, "images/background.png");
	textureHolder.loadAssetFromFile(tileset_texture, "images/tiles.png");	
	textureHolder.loadAssetFromFile(frame_texture, "images/frame.png");		
}

void Game::resetGame()
{
	a = {{0}};
	b = {{0}};
	board = Tetris::Board();
	rotate = false;
	dx = 0;
	timer = 0;
	delay = 0.8;
	normaldelay = 0.8;
	score = 0;
	level = 1;
	totalClearedLines = 0;
	linesToNextLevel = 0;

	generatePiece();
	run();
}
void Game::setupMusic()
{	

	bgm.setLoopPoints(sf::Music::Span(sf::seconds(3.058), sf::seconds(117.356)));
	bgm.setLoop(true);
	bgm.setVolume(25);
	bgm.play();
}

void Game::setupSounds()
{
	bloop.setBuffer(soundBufferHolder.getAssetById(soundBuffer_bloop_buffer));
	bloop.setVolume(50);
	pew.setBuffer(soundBufferHolder.getAssetById(soundBuffer_pew_buffer));
	pew.setVolume(30);
}


void Game::generatePiece()
{
	currentPiece = Tetris::Piece(std::rand() % 7, std::rand() % 7 + 1);
	for (int i = 0; i < 4; i++)
	{
		a.at(i).x = currentPiece.getFigure().at(i) % 2;
		a.at(i).y = currentPiece.getFigure().at(i) / 2;
	}
}

void Game::run()
{
	
	sf::Clock clock;	
	running = true;
	while(window.isOpen() && running) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		

		processEvents();

		if(!paused)
			update();
		dx = 0; 
		rotate = false; 
		delay = normaldelay;
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
			bloop.play();
			if(event.key.code == sf::Keyboard::Up)
				rotate = true;
			else if (event.key.code == sf::Keyboard::Left)
				dx = -1; 
			else if (event.key.code == sf::Keyboard::Right)
				dx = 1;
			else if (event.key.code == sf::Keyboard::Escape)
				paused = !paused;
			else if (event.key.code == sf::Keyboard::R) {
				running = false;
				resetGame();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			delay = 0.0001;
		}
			
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
		b.at(i) = a.at(i);
		a.at(i).x += dx;
	}

	if (!check()) {
		for (int i = 0; i < 4; i++) {
			a.at(i) = b.at(i);
		}
	}
}

void Game::rotatePiece()
{
	if (rotate && currentPiece.getType() != 6) {
		Tetris::Point p = a.at(1); // center of rotation

		for (int i = 0; i < 4; i++) 
		{
			int x = a.at(i).y-p.y;
			int y = a.at(i).x-p.x;
			a.at(i).x = p.x - x;
			a.at(i).y = p.y + y;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++)
				a.at(i) = b.at(i);
		} 
	} 
}

void Game::tick()
{
	if (timer > delay) {
		for (int i = 0; i < 4; i++) {
			b.at(i) = a.at(i);
			a.at(i).y += 1;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				board.getField().at(b.at(i).y).at(b.at(i).x) = currentPiece.getColor();

			}
			score += 1;	
			generatePiece();
		}
		timer = 0;
	}
}

bool Game::check()
{
	auto field = board.getField();
	int M = board.getLines();
	int N = board.getCollumns();
	for (int i=0;i<4;i++)
	  if (a.at(i).x<0 || a.at(i).x>=N || a.at(i).y>=M) {
	      return 0;
	  }

      else if (field.at(a.at(i).y).at(a.at(i).x)) {       	  
      	  return 0;
      }

   return 1;
}

void Game::checkLines()
{
	int M = board.getLines();
	int N = board.getCollumns();
	auto field = board.getField();
	int k = M - 1;
	checkScores();
	for (int i = M - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++ ) {
			if (field.at(i).at(j)) {
				count++;
			}
			board.getField().at(k).at(j) = board.getField().at(i).at(j);			
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
	auto field = board.getField();

	sf::Sprite s(textureHolder.getAssetById(tileset_texture));
	sf::Sprite background(textureHolder.getAssetById(background_texture));
	sf::Sprite frame(textureHolder.getAssetById(frame_texture));

	window.clear();
	window.draw(background);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			if (field.at(i).at(j) == 0)
				continue;
			s.setTextureRect(sf::IntRect(field.at(i).at(j) * 18, 0, 18, 18));
			s.setPosition(j * 18, i * 18);
			s.move(28, 31); // offset
			window.draw(s);
		}

	for (int i = 0; i < 4; i++) {
		s.setTextureRect(sf::IntRect(currentPiece.getColor() * 18, 0, 18, 18));
		s.setPosition(a.at(i).x * 18, a.at(i).y * 18);
		s.move(28,31); //offset
		window.draw(s);
	}
	

	processText();

	window.draw(scoreboard);

	window.draw(frame);
	if(paused)
		window.draw(paused_text);

	window.display();
}

void Game::processText()
{
	processScoreboard();
	processPausedText();
}

void Game::processScoreboard()
{
	std::stringstream ss;
	scoreboard.setFont(fontHolder.getAssetById(font_opensans_bold));
	ss << "Score: " << score << "\n\n";
	ss << "Cleared Lines: " << totalClearedLines << "\n\n";
	ss << "Level: " << level << "\n\n";
	ss << "Cleared lines this level: " << linesToNextLevel << "\n\n";
	ss << "Current Delay: " << normaldelay << "s\n\n";
	scoreboard.setString(ss.str());
	scoreboard.setCharacterSize(18);
	scoreboard.setPosition(379, 22);
	scoreboard.setFillColor(sf::Color::Yellow);
	scoreboard.setOutlineColor(sf::Color::Black);
	scoreboard.setOutlineThickness(3);
}

void Game::processPausedText()
{
	paused_text.setFont(fontHolder.getAssetById(font_opensans_bold));
	paused_text.setString("PAUSED");
	paused_text.setCharacterSize(50);
	paused_text.setPosition(320 / 4, 450 / 2);
	paused_text.setFillColor(sf::Color::Red);
	paused_text.setOutlineColor(sf::Color::Black);
	paused_text.setOutlineThickness(3);
}

// Naive implementation, temporary, works for now.
void Game::checkScores()
{
	int M = board.getLines();
	int N = board.getCollumns();

	int count = 0;
	int linesCleared = 0;

	for(int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if(!board.getField().at(i).at(j)) {
				count = 0;
				continue;
			}
			else
				count++;
		}
		if (count == N) {
			linesCleared++;
			totalClearedLines++;
			linesToNextLevel++;
		} 
		count = 0;
	}	


	if (linesToNextLevel >= 10) {
		level++;
		linesToNextLevel -= 10;
		if (normaldelay > 0.05) {
			normaldelay -= 0.05;
		}
	}
	if (linesCleared != 0) {
		switch(linesCleared) {
			case 1:
				score += 40 * (level + 1);
				pew.setVolume(1);
				break;
			case 2:
				score += 100 * (level + 1);
				pew.setVolume(10);
				break;
			case 3:
				score += 300 * (level + 1);
				pew.setVolume(20);
				break; 
			case 4:
				score += 1200 * (level + 1);
				pew.setVolume(30);
		}
		pew.play();
		std::cout << "kek\n";
	}
	if (linesCleared == 4) {
		std::cout << "TETRIS\n";
	}

}