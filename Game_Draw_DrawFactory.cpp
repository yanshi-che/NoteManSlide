#include "Game_Draw_DrawFactory.h"

Game::Draw::Game_Draw_DrawFactory::Game_Draw_DrawFactory() {
	rane = nullptr;
	beatLine = nullptr;
}

Game::Draw::Game_Draw_RaneDraw* Game::Draw::Game_Draw_DrawFactory::getRaneDrawInstance() {
	if (rane == nullptr) {
		rane = std::make_unique<Game_Draw_RaneDraw>();
	}
	return rane.get();
}

Game::Draw::Game_Draw_BeatLineDraw* Game::Draw::Game_Draw_DrawFactory::getBeatLineDrawInstance() {
	if (beatLine == nullptr) {
		beatLine = std::make_unique<Game_Draw_BeatLineDraw>();
	}
	return beatLine.get();
}