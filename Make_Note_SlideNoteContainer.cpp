#include "Make_Note_SlideNoteContainer.h"

std::uint8_t Make::Note::Make_Note_SlideNoteContainer::lineThickness = 8;

Make::Note::Make_Note_SlideNoteContainer::Make_Note_SlideNoteContainer(const std::uint16_t barID,const std::uint8_t beatID, const double& y,const std::uint8_t laneAmount,const double time) :
	barID(barID), beatID(beatID), laneAmount(laneAmount), time(time), r_y(y) {
	colorR = GetColor(228, 75, 198);
	colorL = GetColor(62, 253, 249);

	laneX.resize(laneAmount + 1);
	double laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX.at(i) = laneWidth * i + Global::DRAW_X_MIN;
	}
	arrowWidthBetween = laneWidth / Global::ARROW_NUM_LANE;

	noteFlag = { false,false };
	noteStartAndEndLane = { {0,0},{0,0} };
}

void Make::Note::Make_Note_SlideNoteContainer::drawArrow() {
	if (r_y < Global::WINDOW_HEIGHT && r_y>0) {
		if (noteFlag.first) {
			if (noteDirectionRightOrLeft.first) {
				for (int i = noteStartAndEndLane.first.second + 1; noteStartAndEndLane.first.first < i; --i) {
					for (int k = 0; k < Global::ARROW_NUM_LANE; ++k) {
						DrawLineAA(static_cast<float>(laneX.at(i) - arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(r_y + Global::ARROW_LENGTH), colorR, lineThickness);
						DrawLineAA(static_cast<float>(laneX.at(i) - arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(r_y - Global::ARROW_LENGTH), colorR, lineThickness);
					}
				}
			}
			else {
				for (int i = noteStartAndEndLane.first.second; i < noteStartAndEndLane.first.first + 1; ++i) {
					for (int k = 0; k < Global::ARROW_NUM_LANE; ++k) {
						DrawLineAA(static_cast<float>(laneX.at(i) + arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(r_y + Global::ARROW_LENGTH), colorR, lineThickness);
						DrawLineAA(static_cast<float>(laneX.at(i) + arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(r_y - Global::ARROW_LENGTH), colorR, lineThickness);
					}
				}
			}
		}
		if (noteFlag.second) {
			if (noteDirectionRightOrLeft.second) {
				for (int i = noteStartAndEndLane.second.second + 1; noteStartAndEndLane.second.first < i; --i) {
					for (int k = 0; k < Global::ARROW_NUM_LANE; ++k) {
						DrawLineAA(static_cast<float>(laneX.at(i) - arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(r_y + Global::ARROW_LENGTH), colorL, lineThickness);
						DrawLineAA(static_cast<float>(laneX.at(i) - arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(r_y - Global::ARROW_LENGTH), colorL, lineThickness);
					}
				}
			}
			else {
				for (int i = noteStartAndEndLane.second.second ; i < noteStartAndEndLane.second.first + 1; ++i) {
					for (int k = 0; k < Global::ARROW_NUM_LANE; ++k) {
						DrawLineAA(static_cast<float>(laneX.at(i) + arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(r_y + Global::ARROW_LENGTH), colorL, lineThickness);
						DrawLineAA(static_cast<float>(laneX.at(i) + arrowWidthBetween * k), static_cast<float>(r_y),
							static_cast<float>(laneX.at(i) + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(r_y - Global::ARROW_LENGTH), colorL, lineThickness);
					}
				}
			}
		}
	}
}

void Make::Note::Make_Note_SlideNoteContainer::drawSlideNote() {
	if (r_y < Global::WINDOW_HEIGHT && r_y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		if (noteFlag.first) {
			if (noteDirectionRightOrLeft.first) {
				DrawLineAA(static_cast<float>(laneX.at(noteStartAndEndLane.first.first)), static_cast<float>(r_y),
					static_cast<float>(laneX.at(noteStartAndEndLane.first.second + 1)), static_cast<float>(r_y), colorR, lineThickness);
			}
			else {
				DrawLineAA(static_cast<float>(laneX.at(noteStartAndEndLane.first.first + 1)), static_cast<float>(r_y),
					static_cast<float>(laneX.at(noteStartAndEndLane.first.second)), static_cast<float>(r_y), colorR,lineThickness);
			}
		}
		if (noteFlag.second) {
			if (noteDirectionRightOrLeft.second) {
				DrawLineAA(static_cast<float>(laneX.at(noteStartAndEndLane.second.first)), static_cast<float>(r_y),
					static_cast<float>(laneX.at(noteStartAndEndLane.second.second + 1)), static_cast<float>(r_y), colorL, lineThickness);
			}
			else {
				DrawLineAA(static_cast<float>(laneX.at(noteStartAndEndLane.second.first + 1)), static_cast<float>(r_y),
					static_cast<float>(laneX.at(noteStartAndEndLane.second.second)), static_cast<float>(r_y), colorL, lineThickness);
			}
		}
		drawArrow();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Note::Make_Note_SlideNoteContainer::setSlideNoteFlag(const std::uint8_t laneIDStart,const std::uint8_t laneIDEnd,const bool right, const bool isDirectionRight) {
	if (right) {
		if (!noteFlag.first) {
			noteStartAndEndLane.first.first = laneIDStart;
			noteStartAndEndLane.first.second = laneIDEnd;
			noteFlag.first = true;
			if (isDirectionRight) {
				noteDirectionRightOrLeft.first = true;
			}
			else {
				noteDirectionRightOrLeft.first = false;
			}
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
			if (isDirectionRight) {
				noteDirectionRightOrLeft.second = true;
			}
			else {
				noteDirectionRightOrLeft.second = false;
			}
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

const std::pair<bool, bool>& Make::Note::Make_Note_SlideNoteContainer::getSlideNoteDirectionRightOrLeft() {
	return noteDirectionRightOrLeft;
}

const std::pair<std::pair<std::uint8_t, std::uint8_t>, std::pair<std::uint8_t, std::uint8_t>>& Make::Note::Make_Note_SlideNoteContainer::getNoteStartAndEnd() {
	return noteStartAndEndLane;
}

const double& Make::Note::Make_Note_SlideNoteContainer::getTime() {
	return time;
}

const std::uint16_t& Make::Note::Make_Note_SlideNoteContainer::getBarID() {
	return barID;
}

const std::uint8_t& Make::Note::Make_Note_SlideNoteContainer::getBeatID() {
	return beatID;
}