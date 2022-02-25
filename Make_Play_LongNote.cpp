#include "Make_Play_LongNote.h"

Make::Play::Make_Play_LongNote::Make_Play_LongNote(const double startTime, const double endTime, const double sixteenthTime, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight, const double laneXLeft, const std::function<void(std::uint8_t, std::uint8_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score) :
	startTime(startTime), endTime(endTime), noteType(noteType), laneIndex(laneIndex), laneXRight(laneXRight), laneXLeft(laneXLeft), nextNote(nextNote), p_score(p_score) {
	p_keyHitCheck = Singleton::Make_Singleton_KeyHitCheck::getInstance();
	y = 0;
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

void Make::Play::Make_Play_LongNote::check(double nowTime) {
	if (turn) {
		if (judgeTimeCount != 0 && 1 <= p_keyHitCheck->getHitKeyForNote(key)) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime && nowTime < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				++judgeTimeCount;
				isHit = true;
			}
		}
		else if (p_keyHitCheck->getHitKeyForNote(key) == 1) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime && nowTime < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				++judgeTimeCount;
				isHit = true;
			}
		}
		else if(judgeTimeCount < judgeTime.size() &&
			nowJudgeTime - Global::GREAT < nowTime && nowTime < nowJudgeTime + Global::GREAT){
			isHit = false;
		}
		if (judgeTimeCount != 0 && startTime < nowTime && nowTime < endTime) {
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

void Make::Play::Make_Play_LongNote::update(double nowTime) {
	y = Global::JUDGELINE_Y - ((startTime - nowTime) * Global::JUDGELINE_Y * Global::hiSpeed);
	longNoteHeight = y - (Global::JUDGELINE_Y - ((endTime - nowTime) * Global::JUDGELINE_Y * Global::hiSpeed));
	if (turn) {
		if (endTime + Global::MISS < nowTime) {
			setDone(true);
		}
		if (judgeTimeCount < judgeTime.size() && nowJudgeTime + Global::GREAT < nowTime) {
			p_score->plusMiss();
			nowJudgeTime = judgeTime.at(judgeTimeCount);
			++judgeTimeCount;
		}
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