#include "Make_Play_NormalNote.h"

Make::Play::Make_Play_NormalNote::Make_Play_NormalNote(const double time, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight, const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote) :
time(time),noteType(noteType),laneIndex(laneIndex),laneXRight(laneXRight),laneXLeft(laneXLeft),nextNote(nextNote){
	y = 0;
	done = false;
	turn = false;
	noteColor = GetColor(255, 255, 255);
}

void Make::Play::Make_Play_NormalNote::check(double nowTime) {
	if (turn) {
		if (y - Global::PERFECT < nowTime && nowTime < y + Global::PERFECT) {

		}
		else if (y - Global::GREAT < nowTime && nowTime < y + Global::GREAT) {

		}else if (y - Global::MISS < nowTime && nowTime < y + Global::MISS) {

		}
	}
}

void Make::Play::Make_Play_NormalNote::setTurn(bool t) {
	turn = t;
}

void Make::Play::Make_Play_NormalNote::setDone(bool b) {

}

void Make::Play::Make_Play_NormalNote::update(double nowTime) {
	y = Global::JUDGELINE_Y - nowTime * Global::JUDGELINE_Y * Global::hiSpeed;
}

void Make::Play::Make_Play_NormalNote::draw() {
	if (0 < y && y < Global::WINDOW_HEIGHT) {
		DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE), static_cast<float>(y),
			static_cast<float>(laneXLeft - Global::LENGTH_FROM_LANE), static_cast<float>(Global::NOTE_HEIGHT + y), GetColor(255, 255, 255), true);
	}
}