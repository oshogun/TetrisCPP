#include "Game.h"

Game::Game():
	currentPiece(1,1),	
	window(sf::VideoMode(640,480), "Tetris C++17 (Name Subject to Change)",sf::Style::Close) 
{	
	assetHolders.loadAssets();
	setupMusic();
	setupSounds();
	resetGame();	
}



void Game::resetGame()
{
	a = {{0}};
	b = {{0}};
	board = Tetris::Board();
	gameVars.resetGameVars();
	pieceCount = {{0}};
	generatePiece();
	run();
}
void Game::setupMusic()
{	
	musicHandler.insertMusic("borb", "music/borb.wav"); 
	musicHandler.setCurrentMusic("borb");
	musicHandler.setLoopPoints(3.058, 120.414);
	musicHandler.setLoop(true);
	musicHandler.setVolume(25);
	musicHandler.play();
}

void Game::setupSounds()
{
	bloop.setBuffer(assetHolders.
						soundBufferHolder.			
							getAssetById(soundBuffer_bloop_buffer));
	bloop.setVolume(50);
	pew.setBuffer(assetHolders.
					soundBufferHolder.
						getAssetById(soundBuffer_pew_buffer));
	pew.setVolume(30);
}


void Game::generatePiece()
{
	int pieceType = std::rand() % 7;
	currentPiece = Tetris::Piece(pieceType, std::rand() % 7 + 1);
	for (int i = 0; i < 4; i++)
	{
		a.at(i).x = currentPiece.getFigure().at(i) % 2;
		a.at(i).y = currentPiece.getFigure().at(i) / 2;
	}
	pieceCount.at(pieceType)++;
}

void Game::run()
{
	
	sf::Clock clock;	
	gameVars.running = true;
	while(window.isOpen() && gameVars.running) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		gameVars.timer += time;
		

		processEvents();

		if(!gameVars.paused && !gameVars.gameOver)
			update();
		gameVars.dx = 0; 
		gameVars.rotate = false; 
		gameVars.delay = gameVars.normaldelay;
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
				gameVars.rotate = true;
			else if (event.key.code == sf::Keyboard::Left)
				gameVars.dx = -1; 
			else if (event.key.code == sf::Keyboard::Right)
				gameVars.dx = 1;
			else if (event.key.code == sf::Keyboard::Escape)
				gameVars.paused = !gameVars.paused;
			else if (event.key.code == sf::Keyboard::R) {
				gameVars.running = false;
				resetGame();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			gameVars.delay = 0.0001;
		}
			
	}
}

void Game::update()
{
	move();
	if (gameVars.rotate && currentPiece.getType() != 6);
		rotatePiece();
	tick();
	checkLines();
}

void Game::move()
{
	for (int i = 0; i < 4; i++) {
		b.at(i) = a.at(i);
		a.at(i).x += gameVars.dx;
	}

	if (!check()) {
		for (int i = 0; i < 4; i++) {
			a.at(i) = b.at(i);
		}
	}
}

void Game::rotatePiece()
{
	if (gameVars.rotate && currentPiece.getType() != 6) {
		Tetris::Point p = a.at(1); // center of rotation
		if (currentPiece.getType() == 0) {
			p = a.at(2);
		}
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
	if (gameVars.timer > gameVars.delay) {
		for (int i = 0; i < 4; i++) {
			b.at(i) = a.at(i);
			a.at(i).y += 1;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				board.getField().at(b.at(i).y).at(b.at(i).x) = currentPiece.getColor();

			}
			gameVars.score += 1;	
			generatePiece();
		}
		gameVars.timer = 0;
	}
}

bool Game::check()
{
	auto field = board.getField();
	int M = board.getLines();
	int N = board.getCollumns();
	for (int i=0;i<4;i++) {
	  if (a.at(i).x<0 || a.at(i).x>=N || a.at(i).y>=M) {
	      return 0;
	  }

      else if (field.at(a.at(i).y).at(a.at(i).x)) {       	  
      	  return 0;
      } 
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

	sf::Sprite s(assetHolders.textureHolder.getAssetById(tileset_texture));
	sf::Sprite background(assetHolders.textureHolder.getAssetById(background_texture));
	sf::Sprite frame(assetHolders.textureHolder.getAssetById(frame_texture));

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
	window.draw(pieceCountText);
	window.draw(frame);
	if(gameVars.paused)
		window.draw(paused_text);

	window.display();
}

void Game::processText()
{
	processScoreboard();
	processPausedText();
	processPieceCountText();
}

void Game::processScoreboard()
{
	std::stringstream ss;
	scoreboard.setFont(assetHolders.fontHolder.getAssetById(font_opensans_bold));
	ss << "Score: " << gameVars.score << "\n\n";
	ss << "Cleared Lines: " << gameVars.totalClearedLines << "\n\n";
	ss << "Level: " << gameVars.level << "\n\n";
	ss << "Cleared lines this level: " << gameVars.linesToNextLevel << "\n\n";
	ss << "Current Delay: " << gameVars.normaldelay << "s\n\n";
	scoreboard.setString(ss.str());
	scoreboard.setCharacterSize(18);
	scoreboard.setPosition(379, 22);
	scoreboard.setFillColor(sf::Color::Yellow);
	scoreboard.setOutlineColor(sf::Color::Black);
	scoreboard.setOutlineThickness(3);
}

void Game::processPausedText()
{
	paused_text.setFont(assetHolders.fontHolder.getAssetById(font_opensans_bold));
	paused_text.setString("PAUSED");
	paused_text.setCharacterSize(50);
	paused_text.setPosition(640 / 4, 450 / 2);
	paused_text.setFillColor(sf::Color::Red);
	paused_text.setOutlineColor(sf::Color::Black);
	paused_text.setOutlineThickness(3);
}


void Game::processPieceCountText() 
{
	std::stringstream ss;
	ss << "\n\nStatistics: \n\n";
	ss << "Lenghty bois: " << pieceCount.at(0) << "\n";
	ss << "Z pieces: " << pieceCount.at(1) << "\n";
	ss << "S pieces: " << pieceCount.at(2) << "\n";
	ss << "T pieces: " << pieceCount.at(3) << "\n";
	ss << "L pieces: " << pieceCount.at(4) << "\n";
	ss << "J pieces: " << pieceCount.at(5) << "\n";
	ss << "Square bois: " << pieceCount.at(6) << "\n"; 
	pieceCountText.setFont(assetHolders.fontHolder.getAssetById(font_opensans_bold));
	pieceCountText.setString(ss.str());
	pieceCountText.setCharacterSize(15);
	pieceCountText.setPosition(379, 247);
	pieceCountText.setFillColor(sf::Color::White);
	pieceCountText.setOutlineColor(sf::Color::Black);
	pieceCountText.setOutlineThickness(3);
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
			gameVars.totalClearedLines++;
			gameVars.linesToNextLevel++;
		} 
		count = 0;
	}	


	if (gameVars.linesToNextLevel >= 10) {
		gameVars.level++;
		gameVars.linesToNextLevel -= 10;
		if (gameVars.normaldelay > 0.05) {
			gameVars.normaldelay -= 0.05;
		}
	}
	if (linesCleared != 0) {
		switch(linesCleared) {
			case 1:
				gameVars.score += 40 * (gameVars.level + 1);
				pew.setVolume(1);
				break;
			case 2:
				gameVars.score += 100 * (gameVars.level + 1);
				pew.setVolume(10);
				break;
			case 3:
				gameVars.score += 300 * (gameVars.level + 1);
				pew.setVolume(20);
				break; 
			case 4:
				gameVars.score += 1200 * (gameVars.level + 1);
				pew.setVolume(30);
		}
		pew.play();
		std::cout << "kek\n";
	}
	if (linesCleared == 4) {
		std::cout << "TETRIS\n";
	}

}