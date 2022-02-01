#include "Game_Note_LongNoteContainer.h"

std::uint8_t Game::Note::Game_Note_LongNoteContainer::noteWidth = 15;

Game::Note::Game_Note_LongNoteContainer::Game_Note_LongNoteContainer(const std::uint16_t& barID, const std::uint16_t& beatID,const std::int32_t& y, const std::uint8_t& amountOfLane,const double& time) :
	r_barID(barID), r_beatID(beatID),r_amountOfLane(amountOfLane),r_time(time),r_y(y) {
	notesHeight.resize(amountOfLane);
	notesX.resize(amountOfLane);
	notesFlag.resize(amountOfLane);
	notesGroup.resize(amountOfLane);
	std::uint16_t laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i < amountOfLane; ++i) {
		notesX[i] = laneWidth * i + Global::DRAW_X_MIN + laneWidth / 2;
		notesFlag[i] = { false,false };
		notesHeight[i] = 0;
	}
	color = GetColor(218, 118, 216);
	notePoint = noteWidth / 2;
}

void Game::Note::Game_Note_LongNoteContainer::drawLongNote() {
	if (r_y < Game::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(notesFlag.size()); i < iSize; ++i) {
			if (notesFlag[i].first && notesFlag[i].second) {
				DrawBox(notesX[i] - notePoint, r_y - notePoint, notesX[i] + notePoint, r_y + notePoint + notesHeight[i], color, true);
			}
		}
	}
}

void Game::Note::Game_Note_LongNoteContainer::setLongNoteFlag(std::uint8_t laneID, bool isFirstOrLast) {
	if (isFirstOrLast) {
		if (!notesFlag[laneID].first) {
			notesFlag[laneID].first = true;
			notesFlag[laneID].second = true;
		}
		else {
			notesFlag[laneID].first = false;
			notesFlag[laneID].second = false;
		}
	}
	else {
		if (!notesFlag[laneID].first) {
			notesFlag[laneID].first = true;
			notesFlag[laneID].second = false;
		}
		else {
			notesFlag[laneID].first = false;
			notesFlag[laneID].second = false;
		}
	}
}

void Game::Note::Game_Note_LongNoteContainer::setNoteHeight(std::uint8_t laneID,std::int32_t noteHeight) {
	this->notesHeight[laneID] = noteHeight;
}

void Game::Note::Game_Note_LongNoteContainer::setLongNoteFlagFirstOrLast(std::uint8_t laneID,bool is) {
	notesFlag[laneID].second = is;
}

void Game::Note::Game_Note_LongNoteContainer::setNoteGroup(std::uint8_t laneID, std::uint16_t group) {
	notesGroup[laneID] = group;
}

const std::int32_t& Game::Note::Game_Note_LongNoteContainer::getY() {
	return r_y;
}

const std::pair<bool, bool> Game::Note::Game_Note_LongNoteContainer::getLongNoteFlag(std::uint8_t laneID) {
	return notesFlag[laneID];
}

const std::vector<std::pair<bool, bool>>& Game::Note::Game_Note_LongNoteContainer::getAllLongNoteFlag() {
	return notesFlag;
}


const std::uint16_t& Game::Note::Game_Note_LongNoteContainer::getNoteGroup(std::uint8_t laneID) {
	return notesGroup[laneID];
}

const double& Game::Note::Game_Note_LongNoteContainer::getTime() {
	return r_time;
}

const std::uint16_t& Game::Note::Game_Note_LongNoteContainer::getBarID() {
	return r_barID;
}

const std::uint16_t& Game::Note::Game_Note_LongNoteContainer::getBeatID() {
	return r_beatID;
}