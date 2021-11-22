#include "Game_Draw_RaneDraw.h"


Game::Draw::Game_Draw_RaneDraw::Game_Draw_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	NumberOfRANE = 6;
}

void Game::Draw::Game_Draw_RaneDraw::raneDraw() const noexcept {
	for (int i = 0; i <= NumberOfRANE; i++) {
		DrawLine((WINDOW_WIDTH/NumberOfRANE)*i, 0, (WINDOW_WIDTH / NumberOfRANE) * i, WINDOW_HEIGHT, raneColor, raneThickness);
	}
}

void Game::Draw::Game_Draw_RaneDraw::draw(){
	raneDraw();
}