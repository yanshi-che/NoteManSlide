#include "Game_Menu_MusicData.h"


Game::Menu::Game_Menu_MusicData::Game_Menu_MusicData(const std::string& musicPath, const std::string& scorePath, const std::string& name, const std::string& artist, const std::uint16_t level, const double bpm, const std::uint16_t barLength, const double totalMinutes, const double beginDelay) :
musicPath(musicPath),scorePath(scorePath),name(name),artist(artist),level(level),bpm(bpm),barLength(barLength),totalMinutes(totalMinutes),beginDelay(beginDelay){

}

const std::string& Game::Menu::Game_Menu_MusicData::getMusicPath() noexcept {
	return musicPath;
}

const std::string& Game::Menu::Game_Menu_MusicData::getScorePath() noexcept {
	return scorePath;
}

const std::string& Game::Menu::Game_Menu_MusicData::getName() noexcept {
	return name;
}

const std::string& Game::Menu::Game_Menu_MusicData::getArtist() noexcept {
	return artist;
}

const std::uint16_t& Game::Menu::Game_Menu_MusicData::getLevel() noexcept {
	return level;
}

const double& Game::Menu::Game_Menu_MusicData::getBpm() noexcept {
	return bpm;
}

const std::uint16_t& Game::Menu::Game_Menu_MusicData::getBarLength() noexcept {
	return barLength;
}
const double& Game::Menu::Game_Menu_MusicData::getTotalMinutes() noexcept {
	return totalMinutes;
}

const double& Game::Menu::Game_Menu_MusicData::getBeginDelay()noexcept {
	return beginDelay;
}