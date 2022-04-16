#include "Game_Play_LongNote.h"

Game::Play::Game_Play_LongNote::Game_Play_LongNote(const double startTime, const double endTime, const double sixteenthTime, const std::uint16_t noteType, const std::uint16_t laneIndex, const double laneXRight, const double laneXLeft, const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Game_Play_Score>& p_score, const std::shared_ptr<Game_Play_Effect>& p_effect, std::uint16_t& maxChain) :
	startTime(startTime), endTime(endTime), noteType(noteType), laneIndex(laneIndex), laneXRight(laneXRight), laneXLeft(laneXLeft), nextNote(nextNote), p_score(p_score),p_effect(p_effect) {
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
	y = 0;
	yUpdateBorderMin = this->startTime - 1 / Config::g_hiSpeed;
	yUpdateBorderMax = this->endTime - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed);
	longNoteHeight = 0;
	alpha = 255;
	done = false;
	turn = false;
	isHit = true;
	noteOutSideColor = GetColor(255, 255, 255);
	nowJudgeTime = startTime;
	judgeTimeCount = 0;
	double t = startTime + sixteenthTime;
	while (t < endTime) {
		judgeTime.push_back(t);
		t += sixteenthTime;
		++maxChain;
	}
	key = 0;
	updateKey();
}

void Game::Play::Game_Play_LongNote::check(double nowTime) {
	if (turn) {
		if (judgeTimeCount != 0 && 1 <= p_keyHitCheck->getHitKeyLong(key) && isHit) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				p_effect->setPerfect(laneIndex);
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				++judgeTimeCount;
				isHit = true;
			}
		}
		else if (p_keyHitCheck->getHitKeyLong(key) == 1) {
			if (judgeTimeCount < judgeTime.size() &&
				nowJudgeTime - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < nowJudgeTime + Global::GREAT) {
				p_score->plusPerfect();
				p_effect->setPerfect(laneIndex);
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

void Game::Play::Game_Play_LongNote::setTurn(bool t) {
	turn = t;
}

void Game::Play::Game_Play_LongNote::setDone(bool d) {
	done = d;
	setTurn(false);
	nextNote(noteType, laneIndex);
}

void Game::Play::Game_Play_LongNote::setYUpdateBorder() {
	yUpdateBorderMin = startTime - 1 / Config::g_hiSpeed;
	yUpdateBorderMax = endTime - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed);
}

void Game::Play::Game_Play_LongNote::update(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax) {
		y = Global::JUDGELINE_Y - ((startTime - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed);
		longNoteHeight = y - (Global::JUDGELINE_Y - ((endTime - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed));
		if (turn) {
			if (endTime + Global::MISS < nowTime + Config::g_judgeCorrection) {
				setDone(true);
			}
			if (judgeTimeCount < judgeTime.size() && nowJudgeTime + Global::GREAT < nowTime + Config::g_judgeCorrection) {
				p_score->plusMiss();
				p_effect->setMiss(laneIndex);
				nowJudgeTime = judgeTime.at(judgeTimeCount);
				isHit = false;
				++judgeTimeCount;
			}
		}
	}
}

void Game::Play::Game_Play_LongNote::updateKey() {
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

void Game::Play::Game_Play_LongNote::draw() {
	if (0 < y && !done) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight),
			static_cast<float>(laneXLeft - Global::LENGTH_FROM_LANE), static_cast<float>(y + Global::NOTE_HEIGHT), noteOutSideColor, true);
		drawNoteStartAndEnd();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Game::Play::Game_Play_LongNote::drawNoteStartAndEnd() {
	//“à‘¤
	if (isHit) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 132);
	}
	//start
	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 1), static_cast<float>(y - Global::NOTE_HEIGHT + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 14), static_cast<float>(y + Global::NOTE_HEIGHT - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 5), static_cast<float>(y - Global::NOTE_HEIGHT + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 10), static_cast<float>(y + Global::NOTE_HEIGHT - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawLineAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 15), static_cast<float>(y - Global::NOTE_HEIGHT),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 15), static_cast<float>(y + Global::NOTE_HEIGHT), noteOutSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 16), static_cast<float>(y - Global::NOTE_HEIGHT + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 49), static_cast<float>(y + Global::NOTE_HEIGHT - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 16), static_cast<float>(y - Global::NOTE_HEIGHT + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 49), static_cast<float>(y + Global::NOTE_HEIGHT - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 30), static_cast<float>(y - Global::NOTE_HEIGHT + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 40), static_cast<float>(y + Global::NOTE_HEIGHT - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	//end
	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 1), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 14), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 5), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 10), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawLineAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 15), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 15), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight), noteOutSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 16), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 49), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 16), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 49), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);

	DrawBoxAA(static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 30), static_cast<float>(y - Global::NOTE_HEIGHT - longNoteHeight + Global::NOTE_LENGTH_FROM_OUTLINE),
		static_cast<float>(laneXRight + Global::LENGTH_FROM_LANE + 40), static_cast<float>(y + Global::NOTE_HEIGHT - longNoteHeight - Global::NOTE_LENGTH_FROM_OUTLINE), noteInSideColor, true);
}