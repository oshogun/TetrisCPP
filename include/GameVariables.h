#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetHolder.hpp"
#include "Assets.h"

struct GameVariables {
	bool rotate, paused, running, gameOver;
	int dx, totalClearedLines, linesToNextLevel, level;
	float timer, delay, normaldelay;
	unsigned score;

	void resetGameVars();
};

struct AssetBank {
	AssetHolder<sf::Texture, Assets> textureHolder;
	AssetHolder<sf::Font, Assets> fontHolder;
	AssetHolder<sf::SoundBuffer, Assets> soundBufferHolder;

	void loadAssets();
};