#include "Make_Play_NormalNote.h"

Make::Play::Make_Play_NormalNote::Make_Play_NormalNote(const double time, const std::uint16_t noteType, const std::uint16_t laneIndex, const double laneXRight, const double laneXLeft,const std::function<void(std::uint16_t, std::uint16_t)> nextNote, std::shared_ptr<Make_Play_Score>& p_score) :
time(time),noteType(noteType),laneIndex(laneIndex),laneXRight(laneXRight),laneXLeft(laneXLeft),nextNote(nextNote),p_score(p_score){
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
	y = 0;
	yUpdateBorderMin = this->time - Global::JUDGELINE_Y / (Global::JUDGELINE_Y * Config::g_hiSpeed);
	yUpdateBorderMax = this->time - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed) + 0.01666;
	done = false;
	turn = false;
	noteColor = GetColor(255, 255, 255);
	key = 0;
	updateKey();
}

void Make::Play::Make_Play_NormalNote::check(double nowTime) {
	if (turn) {
		if (p_keyHitCheck->getHitKeyLong(key) == 1) {
			if (time - Global::PERFECT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < time + Global::PERFECT) {
				setDone(true);
				p_score->plusPerfect();
			}
			else if (time - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < time + Global::GREAT) {
				setDone(true);
				p_score->plusGreat();
			}
			else if (time - Global::MISS < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < time + Global::MISS) {
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

void Make::Play::Make_Play_NormalNote::setYUpdateBorder() {
	yUpdateBorderMin = time - Global::JUDGELINE_Y / (Global::JUDGELINE_Y * Config::g_hiSpeed);
	yUpdateBorderMax = time - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed) + 0.01666;
}

void Make::Play::Make_Play_NormalNote::update(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax) {
		y = Global::JUDGELINE_Y - ((time - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed);
		if (turn && time + Global::MISS < nowTime + Config::g_judgeCorrection) {
			setDone(true);
			p_score->plusMiss();
		}
	}
}

void Make::Play::Make_Play_NormalNote::updateKey() {
	if (laneIndex == 0) {
		key = ::Config::g_lane0;
	}
	else if (laneIndex == 1) {
		key = ::Config::g_lane1;
	}
	else if (laneIndex == 2) {
		key = ::Config::g_lane2;
	}
	else if (laneIndex == 3) {
		key = ::Config::g_lane3;
	}
	else if (laneIndex == 4) {
		key = ::Config::g_lane4;
	}
	else if (laneIndex == 5) {
		key = ::Config::g_lane5;
	}
}

void Make::Play::Make_Play_NormalNote::draw(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax && !done) {
		DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE), static_cast<float>(y - Global::NOTE_HEIGHT),
			static_cast<float>(laneXLeft - Global::LENGTH_FROM_LANE), static_cast<float>(y + Global::NOTE_HEIGHT ), GetColor(255, 255, 255), true);
	}
}

