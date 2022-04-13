#include "Make_Play_LongNote.h"

Make::Play::Make_Play_LongNote::Make_Play_LongNote(const double startTime, const double endTime, const double sixteenthTime, const std::uint16_t noteType, const std::uint16_t laneIndex, const double laneXRight, const double laneXLeft, const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score) :
	startTime(startTime), endTime(endTime), noteType(noteType), laneIndex(laneIndex), laneXRight(laneXRight), laneXLeft(laneXLeft), nextNote(nextNote), p_score(p_score) {
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
	y = 0;
	yUpdateBorderMin = this->startTime - 1 / Config::g_hiSpeed;
	yUpdateBorderMax = this->endTime - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed);
	longNoteHeight = 0;
	alpha = 255;
	done = false;
	turn = false;
	isHit = true;
	noteColor = GetColor(255, 255, 255);
	nowJudgeTime = startTime;
	judgeTimeCount = 0;
	double t = startTime + sixteenthTime;
	while (t < endTime) {
		judgeTime.push_back(t);
		t += sixteenthTime;
	}
	key = 0;
	updateKey();
}

void Make::Play::Make_Play_LongNote::check(double nowTime) {
	if (turn) {
		if (judgeTimeCount != 0 && 1 <= p_keyHitCheck->getHitKeyLong(key) && isHit) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				++judgeTimeCount;
				isHit = true;
			}
		}
		else if (p_keyHitCheck->getHitKeyLong(key) == 1) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				++judgeTimeCount;
				isHit = true;
			}
		}
		if (startTime < nowTime && nowTime < endTime) {
			if (isHit) {
				alpha = 252;
			}
			else {
				alpha = 100;
			}
		}
	}
}

void Make::Play::Make_Play_LongNote::setTurn(bool t) {
	turn = t;
}

void Make::Play::Make_Play_LongNote::setDone(bool d) {
	done = d;
	setTurn(false);
	nextNote(noteType, laneIndex);
}

void Make::Play::Make_Play_LongNote::setYUpdateBorder() {
	yUpdateBorderMin = startTime - 1 / Config::g_hiSpeed;
	yUpdateBorderMax = endTime - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed);
}

void Make::Play::Make_Play_LongNote::update(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax) {
		y = Global::JUDGELINE_Y - ((startTime - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed);
		longNoteHeight = y - (Global::JUDGELINE_Y - ((endTime - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed));
		if (turn) {
			if (endTime + Global::MISS < nowTime + Config::g_judgeCorrection) {
				setDone(true);
			}
			if (judgeTimeCount < judgeTime.size() && nowJudgeTime + Global::GREAT < nowTime + Config::g_judgeCorrection) {
				p_score->plusMiss();
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				isHit = false;
				++judgeTimeCount;
			}
		}
	}
}

void Make::Play::Make_Play_LongNote::updateKey() {
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

void Make::Play::Make_Play_LongNote::draw() {
	if (0 < y && !done) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight),
			static_cast<float>(laneXLeft - Global::LENGTH_FROM_LANE), static_cast<float>(y + Global::NOTE_HEIGHT), GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
