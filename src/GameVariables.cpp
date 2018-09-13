#include "GameVariables.h"

void GameVariables::resetGameVars()
{
	gameOver = false;
	rotate = false;
	paused = false;
	dx = 0;
	timer = 0;
	delay = 0.8;
	normaldelay = 0.8;
	score = 0;
	level = 1;
	totalClearedLines = 0;
	linesToNextLevel = 0;
}