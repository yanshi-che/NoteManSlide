#include "Make_Note_NormalNoteContainer.h"


float Make::Note::Make_Note_NormalNoteContainer::noteWidth = 15.0;

Make::Note::Make_Note_NormalNoteContainer::Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const float& y,const std::uint8_t laneAmount,const float time) :
	barID(barID),beatID(beatID),laneAmount(laneAmount),time(time),r_y(y) {
	noteX.resize(laneAmount);
	noteFlag.resize(laneAmount);
	float laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
	for (int i = 0; i < laneAmount; ++i) {
		noteX.at(i) = laneWidth * i + Global::DRAW_X_MIN + laneWidth * 0.5f;
		noteFlag.at(i) = false;
	}
	color = GetColor(255, 255, 255);
	notePointX = noteWidth * 1.2f;
	notePointY = noteWidth * 0.3f;
}

void Make::Note::Make_Note_NormalNoteContainer::drawNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(noteFlag.size()); i < iSize; ++i) {
			if (noteFlag.at(i)) {
				DrawBoxAA(noteX.at(i) - notePointX, r_y - notePointY, noteX.at(i) + notePointX, r_y + notePointY, color, true);
			}
		}
	}
}

void Make::Note::Make_Note_NormalNoteContainer::setNormalNoteFlag(const std::uint8_t laneID) {
	if (!noteFlag.at(laneID)) {
		noteFlag.at(laneID) = true;
	}
	else {
		noteFlag.at(laneID) = false;
	}
}

const bool Make::Note::Make_Note_NormalNoteContainer::getNormalNoteFlag(const std::uint8_t laneID) {
	return noteFlag.at(laneID);
}

const float& Make::Note::Make_Note_NormalNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_NormalNoteContainer::getBarID() {
	return barID;
}

const std::uint8_t& Make::Note::Make_Note_NormalNoteContainer::getBeatID() {
	return beatID;
}