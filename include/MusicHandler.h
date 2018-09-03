#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class MusicHandler {
public:
	insertMusic(const std::string identifier, const std::string filename);
	removeMusic(const std::string identifier);
	setCurrentMusic(const std::string identifier);
	setVolume(float volume);
	setLoop(float loopStart, float loopEnd); 
	play();
	stop();
private:
	std::unique_ptr<sf::Music> openMusicFromFile(const std::string filename);
private:
	std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicMap;	
}