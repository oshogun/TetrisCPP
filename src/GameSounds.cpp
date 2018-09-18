#include "GameSounds.h"

GameSounds::GameSounds()
{
	loadSounds();
}
void GameSounds::loadSounds()
{
	soundBufferHolder.loadAssetFromFile(soundBuffer_pew_buffer, "soundfx/pew.wav");	
	soundBufferHolder.loadAssetFromFile(soundBuffer_bloop_buffer, "soundfx/beep-02.wav");	
}
void GameSounds::setupSounds()
{
	bloop_effect.setBuffer(soundBufferHolder.			
					getAssetById(soundBuffer_bloop_buffer));
	bloop_effect.setVolume(50);
	pew_effect.setBuffer(soundBufferHolder.
				  getAssetById(soundBuffer_pew_buffer));
	pew_effect.setVolume(30);
}

void GameSounds::setPewVolume(float volume)
{
	pew_effect.setVolume(volume);
}

void GameSounds::setBloopVolume(float volume)
{
	bloop_effect.setVolume(volume);
}

void GameSounds::bloop()
{
	bloop_effect.play();
}

void GameSounds::pew()
{
	pew_effect.play();
}