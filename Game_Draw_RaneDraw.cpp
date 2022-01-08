#include "Game_Draw_RaneDraw.h"

std::uint16_t Game::Draw::Game_Draw_RaneDraw::raneWidth = 0;

Game::Draw::Game_Draw_RaneDraw::Game_Draw_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	numberOfRane = NULL;
}

void Game::Draw::Game_Draw_RaneDraw::draw() noexcept{
	if (numberOfRane != NULL) {
		for (int i = 0; i <= numberOfRane; i++) {
			DrawLine(raneWidth * i + Global::DRAW_X_MIN , 0, raneWidth * i + Global::DRAW_X_MIN , Global::WINDOW_HEIGHT, raneColor, raneThickness);
		}
	}
}

void Game::Draw::Game_Draw_RaneDraw::setNumberOfRane(std::uint8_t num) noexcept {
	numberOfRane = num;
	raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / numberOfRane;
}