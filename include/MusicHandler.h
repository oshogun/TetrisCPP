#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>
#include <stdexcept>
/**
 * @brief      Class for the Music Handler
 * 
 * This handler contains a wrapper for the SFML Music interface,
 * which allows for various music files to be conveniently managed.
 * You can easily open, set loop points, and switch between music 
 * without having to keep track of all your sf::Music objects.
 */
class MusicHandler {
public:
	/**
	 * @brief      Open a music file and insert it into music database
	 *
	 * @param[in]  identifier  The identifier of the music
	 * @param[in]  filename    The filename to open
	 */
	void insertMusic(const std::string & identifier, const std::string & filename);
	/**
	 * @brief      Removes a music from the music database.
	 *
	 * @param[in]  identifier  The identifier of the music
	 */
	void removeMusic(const std::string & identifier);
	/**
	 * @brief      Sets the current music to handle
	 *
	 * @param[in]  identifier  The identifier of the selected music
	 */
	void setCurrentMusic(const std::string & identifier);
	/**
	 * @brief      Sets the volume of the current music
	 *
	 * @param[in]  volume  The volume
	 */
	void setVolume(float volume);
	/**
	 * @brief      Sets the loop points.
	 *
	 * @param[in]  loopStart  The loop start, in seconds.
	 * @param[in]  loopEnd    The loop end (not duration, the actual end time in seconds)
	 */
	void setLoopPoints(float loopStart, float loopEnd); 
	/**
	 * @brief      Begin playback of music
	 */
	void play();
	/**
	 * @brief      Stop playback of music
	 */
	void stop();
	/**
	 * @brief      Sets whether or not to loop the music
	 *
	 * @param[in]  loop  wanna loop?
	 */
	void setLoop(bool loop);
private:
	std::shared_ptr<sf::Music> openMusicFromFile(const std::string & filename);
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Music>> musicMap;	
	std::shared_ptr<sf::Music> currentMusic;
};