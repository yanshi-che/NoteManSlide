#include "Game_MusicDataShareBetweenMenuAndPlay.h"

Game::Game_MusicDataShareBetweenMenuAndPlay::Game_MusicDataShareBetweenMenuAndPlay() {
	p_musicData = nullptr;
}

void Game::Game_MusicDataShareBetweenMenuAndPlay::setMusicData(std::shared_ptr<Menu::Game_Menu_MusicData>& p_musicData) {
	if (this->p_musicData) {
		this->p_musicData.reset();
	}
	this->p_musicData = p_musicData;
}

Game::Menu::Game_Menu_MusicData* Game::Game_MusicDataShareBetweenMenuAndPlay::getMusicData() {
	return p_musicData.get();
}