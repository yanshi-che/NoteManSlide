#include "Game_Note_LongNoteContainer.h"

std::uint8_t Game::Note::Game_Note_LongNoteContainer::noteWidth = 15;

Game::Note::Game_Note_LongNoteContainer::Game_Note_LongNoteContainer(std::int32_t* y, const std::uint8_t* numberOfRane) :
	numberOfRane(numberOfRane) {
	this->y = y;
	noteHeight = 0;
	noteX.resize(*numberOfRane);
	notesFlag.resize(*numberOfRane);
	std::uint16_t raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / *numberOfRane;
	for (int i = 0; i < *numberOfRane; ++i) {
		noteX[i] = raneWidth * i + Global::DRAW_X_MIN + raneWidth / 2;
		notesFlag[i] = { false,false };
	}
	color = GetColor(218, 118, 216);
	notePoint = noteWidth / 2;
}

void Game::Note::Game_Note_LongNoteContainer::setLongNoteFlag(std::uint8_t raneID, bool isFirstOrLast) {
	if (isFirstOrLast) {
		if (!notesFlag[raneID].first) {
			notesFlag[raneID].first = true;
			notesFlag[raneID].second = true;
		}
		else {
			notesFlag[raneID].first = false;
			notesFlag[raneID].second = false;
		}
	}
	else {
		if (!notesFlag[raneID].first) {
			notesFlag[raneID].first = true;
			notesFlag[raneID].second = false;
		}
		else {
			notesFlag[raneID].first = false;
			notesFlag[raneID].second = false;
		}
	}
}

void Game::Note::Game_Note_LongNoteContainer::setNoteHeight(std::int32_t noteHeight) {
	this->noteHeight = noteHeight;
}

const std::int32_t& Game::Note::Game_Note_LongNoteContainer::getY() {
	return *y;
}

void Game::Note::Game_Note_LongNoteContainer::setLastNoteTrue(std::uint8_t raneID) {
	notesFlag[raneID].second = true;
}