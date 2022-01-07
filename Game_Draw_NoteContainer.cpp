#include "Game_Draw_NoteContainer.h"


std::uint8_t Game::Draw::Game_Draw_NoteContainer::noteWidth = 15;
std::uint8_t Game::Draw::Game_Draw_NoteContainer::clickWidth = 5;
int Game::Draw::Game_Draw_NoteContainer::mouseX = 0;
int Game::Draw::Game_Draw_NoteContainer::mouseY = 0;
int Game::Draw::Game_Draw_NoteContainer::button = 0;
int Game::Draw::Game_Draw_NoteContainer::logType = 0;
bool Game::Draw::Game_Draw_NoteContainer::clickObserver = false;

Game::Draw::Game_Draw_NoteContainer::Game_Draw_NoteContainer(std::int32_t* y, std::uint8_t noteID, std::uint16_t raneX, std::uint16_t raneWidth) :
	noteID(noteID) {
	this->y = y;
	this->raneX = raneX;
	this->raneWidth=raneWidth;
	noteFlag = false;
}

bool Game::Draw::Game_Draw_NoteContainer::checkClick() {
	if (clickObserver == false &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true)&&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_DOWN){
		return true;
	}
	return false;
}

void Game::Draw::Game_Draw_NoteContainer::initializeCheckClick() {
	if (clickObserver &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_UP) {
		clickObserver = false;
	}
}

void Game::Draw::Game_Draw_NoteContainer::setNoteFlag() {
	if (std::abs(mouseY - *y) <= clickWidth) {
			if (raneX < mouseX && mouseX < raneX + raneWidth) {
				if (!noteFlag) {
					noteFlag = true;
					clickObserver = true;
				}
				else {
					noteFlag = false;
					clickObserver = true;
				}
			}
	}
}

void Game::Draw::Game_Draw_NoteContainer::drawNote() {
		if (noteFlag) {
			DrawBox(raneWidth * (noteID + 0.5) - noteWidth / 2, *y - noteWidth / 2, raneWidth * (noteID + 0.5) + noteWidth / 2, *y + noteWidth / 2, GetColor(255, 255, 255), true);
		}
}