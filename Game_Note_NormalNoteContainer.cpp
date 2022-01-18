#include "Game_Note_NormalNoteContainer.h"


std::uint8_t Game::Note::Game_Note_NormalNoteContainer::noteWidth = 15;

Game::Note::Game_Note_NormalNoteContainer::Game_Note_NormalNoteContainer(std::int32_t* y,const std::uint8_t* numberOfRane) :
	numberOfRane(numberOfRane) {
	this->y = y;
	noteX.resize(*numberOfRane);
	notesFlag.resize(*numberOfRane);
	std::uint16_t raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / *numberOfRane;
	for (int i = 0; i < *numberOfRane; ++i) {
		noteX[i] = raneWidth * i + Global::DRAW_X_MIN + raneWidth /2;
		notesFlag[i] = false;
	}
	color = GetColor(255, 255, 255);
	notePoint = noteWidth / 2;
}

void Game::Note::Game_Note_NormalNoteContainer::setNoteFlag(std::uint8_t raneID) {
	if (!notesFlag[raneID]) {
		notesFlag[raneID] = true;
	}
	else {
		notesFlag[raneID] = false;
	}
}

bool Game::Note::Game_Note_NormalNoteContainer::getNormalNoteFlag(std::uint8_t raneID) {
	return notesFlag[raneID];
}

std::vector<bool>& Game::Note::Game_Note_NormalNoteContainer::getAllNormalNoteFlag() {
	return notesFlag;
}