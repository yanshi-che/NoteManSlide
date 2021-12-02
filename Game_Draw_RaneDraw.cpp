#include "Game_Draw_RaneDraw.h"


Game::Draw::Game_Draw_RaneDraw::Game_Draw_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	numberOfRane = 6;
}

void Game::Draw::Game_Draw_RaneDraw::raneDraw() const noexcept {
	for (int i = 0; i <= numberOfRane; i++) {
		DrawLine((WINDOW_WIDTH/numberOfRane)*i, 0, (WINDOW_WIDTH / numberOfRane) * i, WINDOW_HEIGHT, raneColor, raneThickness);
	}
}

void Game::Draw::Game_Draw_RaneDraw::draw(){
	raneDraw();
}

void Game::Draw::Game_Draw_RaneDraw::setNumberOfRane(std::uint8_t num) noexcept{
	numberOfRane = num;
}

const std::uint8_t& Game::Draw::Game_Draw_RaneDraw::getNumberOfRane() noexcept{
	return numberOfRane;
}