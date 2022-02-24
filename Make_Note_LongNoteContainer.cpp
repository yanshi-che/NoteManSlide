#include "Make_Note_LongNoteContainer.h"

double Make::Note::Make_Note_LongNoteContainer::noteWidth = 15.0;

Make::Note::Make_Note_LongNoteContainer::Make_Note_LongNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const double& y,const std::uint8_t laneAmount,const double time) :
	barID(barID), beatID(beatID),laneAmount(laneAmount),time(time),r_y(y) {
	noteHeight1.resize(laneAmount);
	noteHeight2.resize(laneAmount);
	noteX.resize(laneAmount);
	noteFlag.resize(laneAmount);
	noteGroup.resize(laneAmount);
	double laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
	for (int i = 0; i < laneAmount; ++i) {
		noteX.at(i) = laneWidth * i + Global::DRAW_X_MIN + laneWidth / 2.0;
		noteFlag.at(i) = { false,false };
		noteHeight1.at(i) = 0;
		noteHeight2.at(i) = 0;
	}
	color = GetColor(255,255,255);
	notePointX = noteWidth * 1.2;
	notePointY = noteWidth * 0.3;
}

void Make::Note::Make_Note_LongNoteContainer::drawLongNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		for (int i = 0, iSize = static_cast<int>(noteFlag.size()); i < iSize; ++i) {
			if (noteFlag.at(i).first && noteFlag.at(i).second) {
				DrawBoxAA(static_cast<float>(noteX.at(i) - notePointX), static_cast<float>(r_y - notePointY - noteHeight1.at(i)),
					static_cast<float>(noteX.at(i) + notePointX), static_cast<float>(r_y + notePointY + noteHeight2.at(i)), color, true);
			}
		}
	}
}

void Make::Note::Make_Note_LongNoteContainer::setLongNoteFlag(const std::uint8_t laneID,const bool isFirstOrLast) {
	if (isFirstOrLast) {
		if (!noteFlag.at(laneID).first) {
			noteFlag.at(laneID).first = true;
			noteFlag.at(laneID).second = true;
		}
		else {
			noteFlag.at(laneID).first = false;
			noteFlag.at(laneID).second = false;
		}
	}
	else {
		if (!noteFlag.at(laneID).first) {
			noteFlag.at(laneID).first = true;
			noteFlag.at(laneID).second = false;
		}
		else {
			noteFlag.at(laneID).first = false;
			noteFlag.at(laneID).second = false;
		}
	}
}

void Make::Note::Make_Note_LongNoteContainer::setNoteHeight(const std::uint8_t laneID,const double noteHeight,const bool isFirst) {
	if (isFirst) {
		this->noteHeight1.at(laneID) = noteHeight;
	}
	else {
		this->noteHeight2.at(laneID) = noteHeight;
	}
}

void Make::Note::Make_Note_LongNoteContainer::setNoteGroup(const std::uint8_t laneID,const std::uint16_t group) {
	noteGroup.at(laneID) = group;
}

const double& Make::Note::Make_Note_LongNoteContainer::getY() {
	return r_y;
}

const std::pair<bool, bool> Make::Note::Make_Note_LongNoteContainer::getLongNoteFlag(const std::uint8_t laneID) {
	return noteFlag.at(laneID);
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getNoteGroup(const std::uint8_t laneID) {
	return noteGroup.at(laneID);
}

const double& Make::Note::Make_Note_LongNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_LongNoteContainer::getBarID() {
	return barID;
}

const std::uint8_t& Make::Note::Make_Note_LongNoteContainer::getBeatID() {
	return beatID;
}