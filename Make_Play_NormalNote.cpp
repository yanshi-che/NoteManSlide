#include "Make_Play_NormalNote.h"

Make::Play::Make_Play_NormalNote::Make_Play_NormalNote(const double time, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight, const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote, std::shared_ptr<Make_Play_Score>& p_score) :
time(time),noteType(noteType),laneIndex(laneIndex),laneXRight(laneXRight),laneXLeft(laneXLeft),nextNote(nextNote),p_score(p_score){
	p_keyHitCheck = Singleton::Make_Singleton_KeyHitCheck::getInstance();
	y = 0;
	done = false;
	turn = false;
	noteColor = GetColor(255, 255, 255);
	if (laneIndex == 0) {
		key = Global::lane0;
	}
	else if (laneIndex == 1) {
		key = Global::lane1;
	}
	else if (laneIndex == 2) {
		key = Global::lane2;
	}
	else if (laneIndex == 3) {
		key = Global::lane3;
	}
	else if (laneIndex == 4) {
		key = Global::lane4;
	}
	else if (laneIndex == 5) {
		key = Global::lane5;
	}
}

void Make::Play::Make_Play_NormalNote::check(double nowTime) {
	if (turn) {
		if (p_keyHitCheck->getHitKeyForNote(key) == 1) {
			if (time - Global::PERFECT < nowTime && nowTime < time + Global::PERFECT) {
				setDone(true);
				p_score->plusPerfect();
			}
			else if (time - Global::GREAT < nowTime && nowTime < time + Global::GREAT) {
				setDone(true);
				p_score->plusGreat();
			}
			else if (time - Global::MISS < nowTime && nowTime < time + Global::MISS) {
				setDone(true);
				p_score->plusMiss();
			}
		}
	}
}

void Make::Play::Make_Play_NormalNote::setTurn(bool t) {
	turn = t;
}

void Make::Play::Make_Play_NormalNote::setDone(bool d) {
	done = d;
	setTurn(false);
	nextNote(noteType,laneIndex);
}

void Make::Play::Make_Play_NormalNote::update(double nowTime) {
	y = Global::JUDGELINE_Y - ((time - nowTime) * Global::JUDGELINE_Y * Global::hiSpeed);
	if (turn && time + Global::MISS < nowTime) {
		setDone(true);
		p_score->plusMiss();
	}
}

void Make::Play::Make_Play_NormalNote::draw() {
	if (0 < y && y < Global::WINDOW_HEIGHT && !done) {
		DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE), static_cast<float>(y - Global::NOTE_HEIGHT),
			static_cast<float>(laneXLeft - Global::LENGTH_FROM_LANE), static_cast<float>(y + Global::NOTE_HEIGHT ), GetColor(255, 255, 255), true);
	}
}