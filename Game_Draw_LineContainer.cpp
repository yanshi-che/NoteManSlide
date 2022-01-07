#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Normal;


Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t bID, const std::uint8_t* numberOfRane, double t, std::uint16_t bNum, std::int32_t y, std::int32_t yMax) :
	barID(bID),time(t),numberOfRane(numberOfRane), barNumber(bNum), yMin(y), yMax(yMax) {
	this->y = y;
	noteType = 1;
	notes.resize(*numberOfRane);
	std::uint16_t raneX = 0;
	std::uint16_t raneWidth = Global::WINDOW_WIDTH / *numberOfRane;
	for (int i = 0; i < *numberOfRane; i++) {
		raneX = raneWidth * i;
		notes[i] = std::make_unique<Game_Draw_NoteContainer>(&(this->y),i,raneX,raneWidth);
	}
	if (barNumber == 0) {
		color = GetColor(0, 0, 255);
		lineThickness = 8;
	}
	else {
		color = GetColor(255, 128, 0);
		lineThickness = 5;
	}
}


void Game::Draw::Game_Draw_LineContainer::drawLine() noexcept {
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		DrawLine(0, y, Global::WINDOW_WIDTH, y, color, lineThickness);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawNotes() noexcept {
	if (noteType == Normal) {
		if (notes[0]->checkClick()) {
			for (int i = 0; i < *numberOfRane; i++) {
				notes[i]->setNoteFlag();
			}
		}
		notes[0]->initializeCheckClick();
	}
	for (int i = 0; i < *numberOfRane; i++) {
		notes[i]->drawNote();
	}
}

void Game::Draw::Game_Draw_LineContainer::setNoteType(std::uint8_t type) noexcept {
	noteType = type;
}

void Game::Draw::Game_Draw_LineContainer::updateY(std::int16_t y) noexcept {
	if (y < 0 && yMin < this->y || 0 < y && this->y < yMax) {
		this->y += y;
	}
}

void Game::Draw::Game_Draw_LineContainer::draw() {
	drawLine();
	drawNotes();
}