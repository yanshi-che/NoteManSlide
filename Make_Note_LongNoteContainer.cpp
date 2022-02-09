#include "Make_Note_LongNoteContainer.h"

float Make::Note::Make_Note_LongNoteContainer::noteWidth = 15.0;

Make::Note::Make_Note_LongNoteContainer::Make_Note_LongNoteContainer(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time) :
	barID(barID), beatID(beatID),amountOfLane(amountOfLane),time(time),r_y(y) {
	notesHeight1.resize(amountOfLane);
	notesHeight2.resize(amountOfLane);
	notesX.resize(amountOfLane);
	notesFlag.resize(amountOfLane);
	notesGroup.resize(amountOfLane);
	float laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i < amountOfLane; ++i) {
		notesX[i] = laneWidth * i + Global::DRAW_X_MIN + laneWidth / 2.0f;
		notesFlag[i] = { false,false };
		notesHeight1[i] = 0;
		notesHeight2[i] = 0;
	}
	color = GetColor(255,255,255);
	notePointX = noteWidth * 1.2f;
	notePointY = noteWidth * 0.3f;
}

void Make::Note::Make_Note_LongNoteContainer::drawLongNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(notesFlag.size()); i < iSize; ++i) {
			if (notesFlag[i].first && notesFlag[i].second) {
				DrawBoxAA(notesX[i] - notePointX, r_y - notePointY - notesHeight1[i], notesX[i] + notePointX, r_y + notePointY + notesHeight2[i], color, true);
			}
		}
	}
}

void Make::Note::Make_Note_LongNoteContainer::setLongNoteFlag(std::uint8_t laneID,bool isFirstOrLast) {
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

void Make::Note::Make_Note_LongNoteContainer::setNoteHeight(std::uint8_t laneID,float noteHeight,bool isOne) {
	if (isOne) {
		this->notesHeight1[laneID] = noteHeight;
	}
	else {
		this->notesHeight2[laneID] = noteHeight;
	}
}

void Make::Note::Make_Note_LongNoteContainer::setNoteGroup(std::uint8_t laneID,std::uint16_t group) {
	notesGroup[laneID] = group;
}

const float& Make::Note::Make_Note_LongNoteContainer::getY() {
	return r_y;
}

const std::pair<bool, bool> Make::Note::Make_Note_LongNoteContainer::getLongNoteFlag(std::uint8_t laneID) {
	return notesFlag[laneID];
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getNoteGroup(std::uint8_t laneID) {
	return notesGroup[laneID];
}

const float& Make::Note::Make_Note_LongNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getBarID() {
	return barID;
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getBeatID() {
	return beatID;
}