#include "Game_PlayResultShare.h"

Game::Game_PlayResultShare::Game_PlayResultShare() {
	perfect = 0;
	great = 0;
	miss = 0;
}

void Game::Game_PlayResultShare::setPerfect(std::uint16_t perfect) {
	this->perfect = perfect;
}

void Game::Game_PlayResultShare::setGreat(std::uint16_t great) {
	this->great = great;
}

void Game::Game_PlayResultShare::setMiss(std::uint16_t miss) {
	this->miss = miss;
}

std::uint16_t Game::Game_PlayResultShare::getPerfect() {
	return perfect;
}

std::uint16_t Game::Game_PlayResultShare::getGreat() {
	return great;
}

std::uint16_t Game::Game_PlayResultShare::getMiss() {
	return miss;
}