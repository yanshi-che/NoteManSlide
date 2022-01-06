#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Normal;
std::uint8_t Game::Draw::Game_Draw_LineContainer::noteWidth = 15;
int Game::Draw::Game_Draw_LineContainer::mouseX = 0;
int Game::Draw::Game_Draw_LineContainer::mouseY = 0;
int Game::Draw::Game_Draw_LineContainer::button = 0;
int Game::Draw::Game_Draw_LineContainer::logType = 0;
bool Game::Draw::Game_Draw_LineContainer::clickObserver = false;

Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t bID, std::uint8_t numOfRane, double t, std::uint16_t bNum, std::int32_t y, std::int32_t yMax) :
	barID(bID), numberOfRane(numOfRane), time(t), barNumber(bNum), yMin(y), yMax(yMax) {
	this->y = y;
	noteType = 1;
	clickWidth = 5;
	raneWidth = Global::WINDOW_WIDTH / numberOfRane;
	raneX.resize(numberOfRane);
	noteFlag.resize(numberOfRane);
	longNoteFlag.resize(numberOfRane);
	for (int i = 0; i < numberOfRane; i++) {
		raneX[i] = raneWidth * i;
		noteFlag[i] = false;
		longNoteFlag[i].resize(2);
		for (int k = 0; k < longNoteFlag[i].size(); k++) {
			longNoteFlag[i][k] = false;
		}
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

void Game::Draw::Game_Draw_LineContainer::drawNote() noexcept {
	if (noteType == Normal) {
		if (clickObserver==false &&
			GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
			button == MOUSE_INPUT_LEFT &&
			logType == MOUSE_INPUT_LOG_DOWN &&
			std::abs(mouseY - y) <= clickWidth) {
			for (int i = 0; i < numberOfRane; i++) {
				if (i != numberOfRane - 1 && raneX[i] < mouseX && mouseX < raneX[i + 1]) {
					if (!noteFlag[i]) {
						noteFlag[i] = true;
						clickObserver = true;
					}
					else {
						noteFlag[i] = false;
						clickObserver = true;
					}
				}else if (i == numberOfRane - 1 && raneX[i] < mouseX && mouseX < Global::WINDOW_WIDTH) {
					if (!noteFlag[i]) {
						noteFlag[i] = true;
						clickObserver = true;
					}
					else {
						noteFlag[i] = false;
						clickObserver = true;
					}
				}
			}
		}
		if (clickObserver &&
			GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
			button == MOUSE_INPUT_LEFT &&
			logType == MOUSE_INPUT_LOG_UP) {
			clickObserver = false;
		}
	}
	for (int i = 0; i < numberOfRane; i++) {
		if (noteFlag[i]) {
			DrawBox(raneWidth * (i + 0.5) - noteWidth / 2, y - noteWidth / 2, raneWidth * (i + 0.5) + noteWidth / 2, y + noteWidth / 2, GetColor(255, 255, 255), true);
		}
	}
}

void Game::Draw::Game_Draw_LineContainer::drawLongNote() noexcept {

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
	drawLongNote();
	drawNote();
}