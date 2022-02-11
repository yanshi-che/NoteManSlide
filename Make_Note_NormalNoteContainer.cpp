#include "Make_Note_NormalNoteContainer.h"


float Make::Note::Make_Note_NormalNoteContainer::noteWidth = 15.0;

Make::Note::Make_Note_NormalNoteContainer::Make_Note_NormalNoteContainer(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time) :
	barID(barID),beatID(beatID),amountOfLane(amountOfLane),time(time),r_y(y) {
	noteX.resize(amountOfLane);
	notesFlag.resize(amountOfLane);
	float laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i < amountOfLane; ++i) {
		noteX.at(i) = laneWidth * i + Global::DRAW_X_MIN + laneWidth * 0.5f;
		notesFlag.at(i) = false;
	}
	color = GetColor(255, 255, 255);
	notePointX = noteWidth * 1.2f;
	notePointY = noteWidth * 0.3f;
}

void Make::Note::Make_Note_NormalNoteContainer::drawNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(notesFlag.size()); i < iSize; ++i) {
			if (notesFlag.at(i)) {
				DrawBoxAA(noteX.at(i) - notePointX, r_y - notePointY, noteX.at(i) + notePointX, r_y + notePointY, color, true);
			}
		}
	}
}

void Make::Note::Make_Note_NormalNoteContainer::setNormalNoteFlag(std::uint8_t laneID) {
	if (!notesFlag.at(laneID)) {
		notesFlag.at(laneID) = true;
	}
	else {
		notesFlag.at(laneID) = false;
	}
}

const bool Make::Note::Make_Note_NormalNoteContainer::getNormalNoteFlag(std::uint8_t laneID) {
	return notesFlag.at(laneID);
}

const float& Make::Note::Make_Note_NormalNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_NormalNoteContainer::getBarID() {
	return barID;
}

const std::uint16_t& Make::Note::Make_Note_NormalNoteContainer::getBeatID() {
	return beatID;
}