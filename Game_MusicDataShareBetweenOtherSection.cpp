#include "Game_MusicDataShareBetweenOtherSection.h"

Game::Game_MusicDataShareBetweenOtherSection::Game_MusicDataShareBetweenOtherSection() {
	p_musicData = nullptr;
	difficulty = 0;
}

void Game::Game_MusicDataShareBetweenOtherSection::setMusicData(std::shared_ptr<Menu::Game_Menu_MusicData>& p_musicData) {
	if (this->p_musicData) {
		this->p_musicData.reset();
	}
	this->p_musicData = p_musicData;
}

void Game::Game_MusicDataShareBetweenOtherSection::setDifficulty(std::uint16_t difficulty) {
	this->difficulty = difficulty;
}

Game::Menu::Game_Menu_MusicData* Game::Game_MusicDataShareBetweenOtherSection::getMusicData() {
	return p_musicData.get();
}

std::uint16_t Game::Game_MusicDataShareBetweenOtherSection::getDifficulty() {
	return difficulty;
}