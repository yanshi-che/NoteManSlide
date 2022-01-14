#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Normal;
std::uint8_t Game::Draw::Game_Draw_LineContainer::clickWidth = 8;
int Game::Draw::Game_Draw_LineContainer::mouseX = 0;
int Game::Draw::Game_Draw_LineContainer::mouseY = 0;
int Game::Draw::Game_Draw_LineContainer::button = 0;
int Game::Draw::Game_Draw_LineContainer::logType = 0;
bool Game::Draw::Game_Draw_LineContainer::clickObserver = false;


Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t* numberOfRane, double time, std::uint16_t beatID, std::int32_t y, std::int32_t yMax) :
	barID(barID),time(time),numberOfRane(numberOfRane), beatID(beatID), yMin(y), yMax(yMax) {
	this->y = y;
	noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	noteManager->makeNoteInstance(barID,beatID,&this->y,numberOfRane);
	raneX.resize(*numberOfRane + 1);
	std::uint16_t raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / *numberOfRane;
	for (int i = 0; i <= *numberOfRane; i++) {
		raneX[i] = raneWidth * i + Global::DRAW_X_MIN;
	}
	if (beatID == 0) {
		color = GetColor(0, 0, 255);
		lineThickness = 8;
	}
	else {
		color = GetColor(255, 128, 0);
		lineThickness = 5;
	}
}

void Game::Draw::Game_Draw_LineContainer::drawBarID() noexcept {
	if (beatID == 0 && y < Game::Global::WINDOW_HEIGHT && y>0) {
		DrawFormatString( 0 , y - lineThickness /2, GetColor(255, 255, 255), "%d" , barID + 1);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawLine() noexcept {
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		DrawLine(Global::DRAW_X_MIN, y, Global::DRAW_X_MAX, y, color, lineThickness);
	}
}

bool Game::Draw::Game_Draw_LineContainer::checkClick() {
	if (clickObserver == false &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_DOWN) {
		return true;
	}
	return false;
}

void Game::Draw::Game_Draw_LineContainer::initializeCheckClick() {
	if (clickObserver &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_UP) {
		clickObserver = false;
	}
}

void Game::Draw::Game_Draw_LineContainer::drawNotes() noexcept {
	if (noteType == Normal) {
		if (checkClick()&&
			std::abs(mouseY - y) <= clickWidth) {
			for (int i = 0; i < raneX.size() -1; i++) {
				if (raneX[i] < mouseX && mouseX < raneX[i+1]) {
					noteManager->setNote(barID, beatID, i);
					clickObserver = true;
					break;
				}
			}
		}
		initializeCheckClick();
	}
	noteManager->draw();
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
	drawBarID();
	drawNotes();
}