#include "Make_Note_SlideNoteContainer.h"

std::uint8_t Make::Note::Make_Note_SlideNoteContainer::lineThickness = 8;

Make::Note::Make_Note_SlideNoteContainer::Make_Note_SlideNoteContainer(const std::uint16_t barID,const std::uint8_t beatID, const float& y,const std::uint8_t amountOfLane,const float time) :
	barID(barID), beatID(beatID), amountOfLane(amountOfLane), time(time), r_y(y) {
	colorR = GetColor(228, 75, 198);
	colorL = GetColor(62, 253, 249);

	laneX.resize(amountOfLane + 1);
	float laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i <= amountOfLane; ++i) {
		laneX.at(i) = laneWidth * i + Global::DRAW_X_MIN;
	}
	arrowWidthBetween = laneWidth / arrowNumInLane;

	noteFlag = { false,false };
	noteStartAndEndLane = { {0,0},{0,0} };
}

void Make::Note::Make_Note_SlideNoteContainer::drawArrow() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		if (noteFlag.first) {
			for (int i = noteStartAndEndLane.first.second; i < noteStartAndEndLane.first.first + 1 ; ++i) {
				for (int k = 0; k < arrowNumInLane; ++k) {
					DrawLineAA(laneX.at(i) + arrowWidthBetween * k, r_y, laneX.at(i) + arrowWidthBetween * k + arrowHeight, r_y + arrowLength, colorR, lineThickness);
					DrawLineAA(laneX.at(i) + arrowWidthBetween * k, r_y, laneX.at(i) + arrowWidthBetween * k + arrowHeight, r_y - arrowLength, colorR, lineThickness);
				}
			}
		}
		if (noteFlag.second) {
			for (int i = noteStartAndEndLane.second.second + 1; noteStartAndEndLane.second.first < i ; --i) {
				for (int k = 0; k < arrowNumInLane; ++k) {
					DrawLineAA(laneX.at(i) - arrowWidthBetween * k, r_y, laneX.at(i) - arrowWidthBetween * k - arrowHeight, r_y + arrowLength, colorL, lineThickness);
					DrawLineAA(laneX.at(i) - arrowWidthBetween * k, r_y, laneX.at(i) - arrowWidthBetween * k - arrowHeight, r_y - arrowLength, colorL, lineThickness);
				}
			}
		}
	}
}

void Make::Note::Make_Note_SlideNoteContainer::drawSlideNote() {
	if (r_y < Make::Global::WINDOW_HEIGHT && r_y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		drawArrow();
		if (noteFlag.first) {
			DrawLineAA(laneX.at(noteStartAndEndLane.first.first + 1), r_y, laneX.at(noteStartAndEndLane.first.second), r_y, colorR,lineThickness);
		}
		if (noteFlag.second) {
			DrawLineAA(laneX.at(noteStartAndEndLane.second.first), r_y, laneX.at(noteStartAndEndLane.second.second + 1), r_y, colorL,lineThickness);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Note::Make_Note_SlideNoteContainer::setSlideNoteFlag(const std::uint8_t laneIDStart,const std::uint8_t laneIDEnd,const bool right) {
	if (right) {
		if (!noteFlag.first) {
			noteStartAndEndLane.first.first = laneIDStart;
			noteStartAndEndLane.first.second = laneIDEnd;
			noteFlag.first = true;
		}
		else {
			noteStartAndEndLane.first.first = NULL;
			noteStartAndEndLane.first.second = NULL;
			noteFlag.first = false;
		}
	}
	else {
		if (!noteFlag.second) {
			noteStartAndEndLane.second.first = laneIDStart;
			noteStartAndEndLane.second.second = laneIDEnd;
			noteFlag.second = true;
		}
		else {
			noteStartAndEndLane.second.first = NULL;
			noteStartAndEndLane.second.second = NULL;
			noteFlag.second = false;
		}
	}
}

const std::pair<bool, bool>& Make::Note::Make_Note_SlideNoteContainer::getSlideNoteFlag() {
	return noteFlag;
}

const std::pair<std::pair<std::uint8_t, std::uint8_t>, std::pair<std::uint8_t, std::uint8_t>>& Make::Note::Make_Note_SlideNoteContainer::getNoteStartAndEnd() {
	return noteStartAndEndLane;
}

const float& Make::Note::Make_Note_SlideNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_SlideNoteContainer::getBarID() {
	return barID;
}

const std::uint8_t& Make::Note::Make_Note_SlideNoteContainer::getBeatID() {
	return beatID;
}