#include "Game_Note_NoteContainer.h"


std::uint8_t Game::Note::Game_Note_NoteContainer::noteWidth = 15;
std::uint8_t Game::Note::Game_Note_NoteContainer::clickWidth = 5;
int Game::Note::Game_Note_NoteContainer::mouseX = 0;
int Game::Note::Game_Note_NoteContainer::mouseY = 0;
int Game::Note::Game_Note_NoteContainer::button = 0;
int Game::Note::Game_Note_NoteContainer::logType = 0;
bool Game::Note::Game_Note_NoteContainer::clickObserver = false;

Game::Note::Game_Note_NoteContainer::Game_Note_NoteContainer(std::int32_t* y, std::uint8_t noteID, std::uint16_t raneX, std::uint16_t raneWidth) :
	noteID(noteID) {
	this->y = y;
	this->raneX = raneX;
	this->raneWidth=raneWidth;
	noteFlag = false;
	color = GetColor(255, 255, 255);
	noteX = raneX + raneWidth /2;
	notePoint = noteWidth / 2;
}

bool Game::Note::Game_Note_NoteContainer::checkClick() {
	if (clickObserver == false &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true)&&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_DOWN){
		return true;
	}
	return false;
}

void Game::Note::Game_Note_NoteContainer::initializeCheckClick() {
	if (clickObserver &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		button == MOUSE_INPUT_LEFT &&
		logType == MOUSE_INPUT_LOG_UP) {
		clickObserver = false;
	}
}

void Game::Note::Game_Note_NoteContainer::setNoteFlag() {
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

void Game::Note::Game_Note_NoteContainer::drawNote() {
	if (noteFlag) {
		DrawBox(noteX - notePoint , *y - notePoint, noteX + notePoint , *y + notePoint, color, true);
	}
}

bool& Game::Note::Game_Note_NoteContainer::getNoteFlag() {
	return noteFlag;
}