#include "MusicHandler.h"
#include <iostream>

void MusicHandler::insertMusic(const std::string & identifier, const std::string & filename)
{
	auto musicPtr = openMusicFromFile(filename);
	auto mapEntry = std::make_pair(identifier, musicPtr);
	musicMap.insert(mapEntry);
}

void MusicHandler::removeMusic(const std::string & identifier)
{
	musicMap.erase(identifier);
}

void MusicHandler::setCurrentMusic(const std::string & identifier)
{
	auto found = musicMap.find(identifier);
	assert(found != musicMap.end());

	currentMusic = found->second;
}

void MusicHandler::setVolume(float volume)
{
	currentMusic->setVolume(volume);
}

void MusicHandler::setLoopPoints(float loopStart, float loopEnd)
{
	float duration = loopEnd - loopStart;
	auto startSecs = sf::seconds(loopStart);
	auto durationSecs = sf::seconds(duration); 
	auto timeSpan = sf::Music::Span<sf::Time>(startSecs, durationSecs);
	currentMusic->setLoopPoints(timeSpan);
}

void MusicHandler::setLoop(bool loop)
{
	currentMusic->setLoop(loop);
}

void MusicHandler::play()
{
	currentMusic->play();
}

void MusicHandler::stop()
{
	currentMusic->stop();
}

std::shared_ptr<sf::Music> MusicHandler::openMusicFromFile(const std::string & filename)
{
	auto music = std::make_shared<sf::Music>();
	if (!music -> openFromFile(filename)) {
		throw std::runtime_error("Failed to load file: " + filename);
	}
	return music;
}