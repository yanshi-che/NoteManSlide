#include "Game_Draw_BeatLineDraw.h"

void Game::Draw::Game_Draw_BeatLineDraw::setMusicData(File::Game_File_MusicData* data) {
	musicData = data;
}

void Game::Draw::Game_Draw_BeatLineDraw::setQuontize(std::uint8_t quon) {
	quontize = quon;
}

