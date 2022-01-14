#include "Game_Note_NoteContainer.h"


std::uint8_t Game::Note::Game_Note_NoteContainer::noteWidth = 15;

Game::Note::Game_Note_NoteContainer::Game_Note_NoteContainer(std::int32_t* y,const std::uint8_t* numberOfRane) :
	numberOfRane(numberOfRane) {
	this->y = y;
	noteX.resize(*numberOfRane);
	notesFlag.resize(*numberOfRane);
	std::uint16_t raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / *numberOfRane;
	for (int i = 0; i < *numberOfRane; i++) {
		noteX[i] = raneWidth * i + Global::DRAW_X_MIN + raneWidth /2;
		notesFlag[i] = false;
	}
	color = GetColor(255, 255, 255);
	notePoint = noteWidth / 2;
}

void Game::Note::Game_Note_NoteContainer::setNoteFlag(std::uint8_t raneID) {
	if (!notesFlag[raneID]) {
		notesFlag[raneID] = true;
	}
	else {
		notesFlag[raneID] = false;
	}
}

void Game::Note::Game_Note_NoteContainer::drawNote() {
	if (*y < Game::Global::WINDOW_HEIGHT && *y>0) {
		for (int i = 0; i < notesFlag.size(); i++) {
			if (notesFlag[i]) {
				DrawBox(noteX[i] - notePoint, *y - notePoint, noteX[i] + notePoint, *y + notePoint, color, true);
			}
		}
	}
}

std::vector<bool>& Game::Note::Game_Note_NoteContainer::getNoteFlag() {
	return notesFlag;
}