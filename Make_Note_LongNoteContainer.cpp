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
		notesX.at(i) = laneWidth * i + Global::DRAW_X_MIN + laneWidth / 2.0f;
		notesFlag.at(i) = { false,false };
		notesHeight1.at(i) = 0;
		notesHeight2.at(i) = 0;
	}
	color = GetColor(255,255,255);
	notePointX = noteWidth * 1.2f;
	notePointY = noteWidth * 0.3f;
}

void Make::Note::Make_Note_LongNoteContainer::drawLongNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(notesFlag.size()); i < iSize; ++i) {
			if (notesFlag.at(i).first && notesFlag.at(i).second) {
				DrawBoxAA(notesX.at(i) - notePointX, r_y - notePointY - notesHeight1.at(i), notesX.at(i) + notePointX, r_y + notePointY + notesHeight2.at(i), color, true);
			}
		}
	}
}

void Make::Note::Make_Note_LongNoteContainer::setLongNoteFlag(std::uint8_t laneID,bool isFirstOrLast) {
	if (isFirstOrLast) {
		if (!notesFlag.at(laneID).first) {
			notesFlag.at(laneID).first = true;
			notesFlag.at(laneID).second = true;
		}
		else {
			notesFlag.at(laneID).first = false;
			notesFlag.at(laneID).second = false;
		}
	}
	else {
		if (!notesFlag.at(laneID).first) {
			notesFlag.at(laneID).first = true;
			notesFlag.at(laneID).second = false;
		}
		else {
			notesFlag.at(laneID).first = false;
			notesFlag.at(laneID).second = false;
		}
	}
}

void Make::Note::Make_Note_LongNoteContainer::setNoteHeight(std::uint8_t laneID,float noteHeight,bool isFirst) {
	if (isFirst) {
		this->notesHeight1.at(laneID) = noteHeight;
	}
	else {
		this->notesHeight2.at(laneID) = noteHeight;
	}
}

void Make::Note::Make_Note_LongNoteContainer::setNoteGroup(std::uint8_t laneID,std::uint16_t group) {
	notesGroup.at(laneID) = group;
}

const float& Make::Note::Make_Note_LongNoteContainer::getY() {
	return r_y;
}

const std::pair<bool, bool> Make::Note::Make_Note_LongNoteContainer::getLongNoteFlag(std::uint8_t laneID) {
	return notesFlag.at(laneID);
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getNoteGroup(std::uint8_t laneID) {
	return notesGroup.at(laneID);
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