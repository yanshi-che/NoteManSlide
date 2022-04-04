#include "Game_Menu_MusicData.h"


Game::Menu::Game_Menu_MusicData::Game_Menu_MusicData(const std::string& musicPath, const std::string& scorePath, const std::string& savePath, const std::string& name, const std::string& artist, const std::uint16_t level, const double bpm, const std::uint16_t barLength, const double totalMinutes, const double beginDelay) :
musicPath(musicPath),scorePath(scorePath),savePath(savePath),name(name),artist(artist),level(level),bpm(bpm),barLength(barLength),totalMinutes(totalMinutes),beginDelay(beginDelay){
	isPerfect = false;
	isFullChain = false;
	isClear = false;
	bestScore = NULL;
}

const std::string& Game::Menu::Game_Menu_MusicData::getMusicPath() noexcept {
	return musicPath;
}

const std::string& Game::Menu::Game_Menu_MusicData::getScorePath() noexcept {
	return scorePath;
}

const std::string& Game::Menu::Game_Menu_MusicData::getSavePath() noexcept {
	return savePath;
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

const bool& Game::Menu::Game_Menu_MusicData::getIsPerfect() noexcept {
	return isPerfect;
}

const bool& Game::Menu::Game_Menu_MusicData::getIsFullChain() noexcept {
	return isFullChain;
}

const bool& Game::Menu::Game_Menu_MusicData::getIsClear() noexcept {
	return isClear;
}

const std::uint16_t& Game::Menu::Game_Menu_MusicData::getBestScore() noexcept {
	return bestScore;
}

void Game::Menu::Game_Menu_MusicData::setIsPerfect(const bool isPerfect) noexcept {
	this->isPerfect = isPerfect;
}

void Game::Menu::Game_Menu_MusicData::setIsFullChain(const bool isFullChain) noexcept {
	this->isFullChain = isFullChain;
}

void Game::Menu::Game_Menu_MusicData::setIsClear(const bool isClear) noexcept {
	this->isClear = isClear;
}

void Game::Menu::Game_Menu_MusicData::setBestScore(const std::uint16_t bestScore) noexcept {
	this->bestScore = bestScore;
}