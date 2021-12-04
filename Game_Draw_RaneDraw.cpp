#include "Game_Draw_RaneDraw.h"

Game::Draw::Game_Draw_RaneDraw::Game_Draw_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	numberOfRane = 4;
}

void Game::Draw::Game_Draw_RaneDraw::draw() noexcept{
	for (int i = 0; i <= numberOfRane; i++) {
		DrawLine((Global::WINDOW_WIDTH / numberOfRane) * i, 0, (Global::WINDOW_WIDTH / numberOfRane) * i, Global::WINDOW_HEIGHT, raneColor, raneThickness);
	}
}

void Game::Draw::Game_Draw_RaneDraw::setNumberOfRane(std::uint8_t num) noexcept{
	numberOfRane = num;
}

const std::uint8_t& Game::Draw::Game_Draw_RaneDraw::getNumberOfRane() noexcept{
	return numberOfRane;
}