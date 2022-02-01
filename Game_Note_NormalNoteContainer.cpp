#include "Game_Note_NormalNoteContainer.h"


std::uint8_t Game::Note::Game_Note_NormalNoteContainer::noteWidth = 15;

Game::Note::Game_Note_NormalNoteContainer::Game_Note_NormalNoteContainer(const std::uint16_t& barID, const std::uint16_t& beatID,const std::int32_t& y,const std::uint8_t& amountOfLane,const double& time) :
	r_barID(barID),r_beatID(beatID),r_amountOfLane(amountOfLane),r_time(time),r_y(y) {
	noteX.resize(amountOfLane);
	notesFlag.resize(amountOfLane);
	std::uint16_t laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i < amountOfLane; ++i) {
		noteX[i] = laneWidth * i + Global::DRAW_X_MIN + laneWidth /2;
		notesFlag[i] = false;
	}
	color = GetColor(255, 255, 255);
	notePoint = noteWidth / 2;
}

void Game::Note::Game_Note_NormalNoteContainer::drawNote() {
	if (r_y < Game::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(notesFlag.size()); i < iSize; ++i) {
			if (notesFlag[i]) {
				DrawBox(noteX[i] - notePoint, r_y - notePoint, noteX[i] + notePoint, r_y + notePoint, color, true);
			}
		}
	}
}

void Game::Note::Game_Note_NormalNoteContainer::setNormalNoteFlag(std::uint8_t laneID) {
	if (!notesFlag[laneID]) {
		notesFlag[laneID] = true;
	}
	else {
		notesFlag[laneID] = false;
	}
}

const bool Game::Note::Game_Note_NormalNoteContainer::getNormalNoteFlag(std::uint8_t laneID) {
	return notesFlag[laneID];
}

const std::vector<bool>& Game::Note::Game_Note_NormalNoteContainer::getAllNormalNoteFlag() {
	return notesFlag;
}

const double& Game::Note::Game_Note_NormalNoteContainer::getTime() {
	return r_time;
}

const std::uint16_t& Game::Note::Game_Note_NormalNoteContainer::getBarID() {
	return r_barID;
}

const std::uint16_t& Game::Note::Game_Note_NormalNoteContainer::getBeatID() {
	return r_beatID;
}