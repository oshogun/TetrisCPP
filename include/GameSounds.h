#pragma once

#include <SFML/Audio.hpp>
#include "AssetHolder.hpp"
#include "Assets.h"

class GameSounds {
public:
	GameSounds();
	void loadSounds();
	void setupSounds();
	void setPewVolume(float volume);
	void setBloopVolume(float volume);
	void bloop();
	void pew();

private:
	AssetHolder<sf::SoundBuffer, Assets> soundBufferHolder;
	sf::Sound bloop_effect, pew_effect;
};