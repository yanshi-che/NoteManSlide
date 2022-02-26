#include "Make_Play_SlideNote.h"

Make::Play::Make_Play_SlideNote::Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth, const double arrowWidthBetween, const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft, const std::uint8_t slideLaneIndexStart, const std::uint8_t slideLaneIndexEnd, const std::function<void(std::uint8_t, std::uint8_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score) :
	time(time), noteType(noteType), laneXStart(laneXStart), laneXEnd(laneXEnd),laneWidth(laneWidth), arrowWidthBetween(arrowWidthBetween), rightOrLeft(rightOrLeft), directionRightOrLeft(directionRightOrLeft), slideLaneIndexStart(slideLaneIndexStart), slideLaneIndexEnd(slideLaneIndexEnd), nextNote(nextNote), p_score(p_score) {
	p_keyHitCheck = Singleton::Make_Singleton_KeyHitCheck::getInstance();
	colorR = GetColor(228, 75, 198);
	colorL = GetColor(62, 253, 249);
	y = 0;
	done = false;
	turn = false;
	key = 0;
	updateKey();
}

void Make::Play::Make_Play_SlideNote::check(double nowTime) {
	if (turn) {
		if(1 <= p_keyHitCheck->getHitKeyForNote(key))
		if (time - Global::GREAT< nowTime + Global::g_judgeCorrection && nowTime + Global::g_judgeCorrection < time + Global::GREAT) {
			setDone(true);
			p_score->plusPerfect();
		}
	}
}

void Make::Play::Make_Play_SlideNote::setTurn(bool t) {
	turn = t;
}

void Make::Play::Make_Play_SlideNote::setDone(bool d) {
	done = d;
	setTurn(false);
	nextNote(noteType, rightOrLeft);
}

void Make::Play::Make_Play_SlideNote::update(double nowTime) {
	y = Global::JUDGELINE_Y - ((time - nowTime) * Global::JUDGELINE_Y * Global::g_hiSpeed);
	if (turn && time + Global::MISS < nowTime + Global::g_judgeCorrection) {
		setDone(true);
		p_score->plusMiss();
	}
}

void Make::Play::Make_Play_SlideNote::updateKey() {
	if (rightOrLeft == 0 && directionRightOrLeft == 0) {
		key = Global::g_laneRR;
	}
	else if (rightOrLeft == 0 && directionRightOrLeft == 1) {
		key = Global::g_laneRL;
	}
	else if (rightOrLeft == 1 && directionRightOrLeft == 0) {
		key = Global::g_laneLR;
	}
	else if (rightOrLeft == 1 && directionRightOrLeft == 1) {
		key = Global::g_laneLL;
	}
}

void Make::Play::Make_Play_SlideNote::drawLine() {
	if (rightOrLeft == 0) {
		DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorR, 3);
	}
	else {
		DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorL, 3);
	}
}

void Make::Play::Make_Play_SlideNote::drawArrow() {
	if (directionRightOrLeft == 0) {
		for (int i = 0, iSize = slideLaneIndexEnd - slideLaneIndexStart + 1; i < iSize; ++i) {
			for (int k = 0, kSize = Global::ARROW_NUM_LANE; k < kSize; ++k) {
				if (rightOrLeft == 0) {
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd  - laneWidth * i -arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorR, 3);
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorR, 3);
				}
				else {
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorL, 3);
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorL, 3);
				}
			}
		}
	}
	else {
		for (int i = 0, iSize = slideLaneIndexStart - slideLaneIndexEnd + 1; i < iSize; ++i) {
			for (int k = 0, kSize = Global::ARROW_NUM_LANE; k < kSize; ++k) {
				if (rightOrLeft == 0) {
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorR, 3);
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k	), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorR, 3);
				}
				else {
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorL, 3);
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorL, 3);
				}
			}
		}
	}
}

void Make::Play::Make_Play_SlideNote::draw() {
	if (0 < y && y < Global::WINDOW_HEIGHT && !done) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		drawLine();
		drawArrow();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
