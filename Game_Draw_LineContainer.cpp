#include "Game_Draw_LineContainer.h"

Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t bID, std::uint8_t numOfRane, double t, std::uint16_t bNum,std::int32_t y):
	barID(bID), numberOfRane(numOfRane),time(t), barNumber(bNum){
	this->y = y;
	notesFlag.resize(numberOfRane);
	for (int i = 0; i < numberOfRane; i++) {
		notesFlag[i] = false;
	}
	if (barNumber == 0) {
		color = GetColor(0, 0, 255);
		thickness = 8;
	}
	else {
		color = GetColor(255, 128, 0);
		thickness = 5;
	}
}


void Game::Draw::Game_Draw_LineContainer::drawLine() noexcept{
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		DrawLine(0, y, Global::WINDOW_WIDTH, y, color, thickness);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawNote() noexcept{

}

void Game::Draw::Game_Draw_LineContainer::updateY(std::int16_t y) noexcept {
	if ( y < 0 && yMin < this->y || 0 < y && this->y < yMax) {
		this->y += y;
	}
}

void Game::Draw::Game_Draw_LineContainer::setYMax(std::int32_t yMa) noexcept {
	this->yMax = yMa;
}

void Game::Draw::Game_Draw_LineContainer::setYMin(std::int32_t yMi) noexcept {
	this->yMin = yMi;
}

void Game::Draw::Game_Draw_LineContainer::draw() {
	drawLine();
}