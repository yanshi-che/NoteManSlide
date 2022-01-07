#include "Game_Draw_RaneDraw.h"

Game::Draw::Game_Draw_RaneDraw::Game_Draw_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	numberOfRane = NULL;
}

void Game::Draw::Game_Draw_RaneDraw::draw() noexcept{
	if (numberOfRane != NULL) {
		for (int i = 0; i <= numberOfRane; i++) {
			DrawLine((Global::WINDOW_WIDTH / numberOfRane) * i, 0, (Global::WINDOW_WIDTH / numberOfRane) * i, Global::WINDOW_HEIGHT, raneColor, raneThickness);
		}
	}
}

void Game::Draw::Game_Draw_RaneDraw::setNumberOfRane(std::uint8_t num) noexcept {
	numberOfRane = num;
}