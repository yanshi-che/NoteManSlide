#include "Make_Play_SlideNote.h"

Make::Play::Make_Play_SlideNote::Make_Play_SlideNote(const double time, const std::uint16_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth, const double arrowWidthBetween, const std::uint16_t rightOrLeft, const std::uint16_t directionRightOrLeft, const std::uint16_t slideLaneIndexStart, const std::uint16_t slideLaneIndexEnd, const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score, const std::shared_ptr<Game::Play::Game_Play_Effect>& p_effect, const std::shared_ptr<Game::Play::Game_Play_SoundEffect>& p_soundEffect) :
	time(time), noteType(noteType), laneXStart(laneXStart), laneXEnd(laneXEnd),laneWidth(laneWidth), arrowWidthBetween(arrowWidthBetween), rightOrLeft(rightOrLeft), directionRightOrLeft(directionRightOrLeft), slideLaneIndexStart(slideLaneIndexStart), slideLaneIndexEnd(slideLaneIndexEnd), nextNote(nextNote), p_score(p_score),p_effect(p_effect),p_soundEffect(p_soundEffect) {
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
	colorRR = GetColor(255, 49, 55);
	colorRL = GetColor(228, 75, 198);
	colorLR = GetColor(62, 253, 249);
	colorLL = GetColor(67, 62, 253);
	y = 0;
	yUpdateBorderMin = this->time - Global::JUDGELINE_Y / (Global::JUDGELINE_Y * Config::g_hiSpeed);
	yUpdateBorderMax = this->time - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed) + 0.01666;
	done = false;
	turn = false;
	isAuto = false;
	key = 0;
	updateKey();
}

void Make::Play::Make_Play_SlideNote::check(double nowTime) {
	if (turn) {
		if (isAuto && time - Global::sixtyFpsTime < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < time + Global::sixtyFpsTime) {
			setDone(true);
			p_score->plusPerfect();
			p_soundEffect->playSoundEffect();
			if (directionRightOrLeft == 0) {
				for (int i = slideLaneIndexStart; i <= slideLaneIndexEnd; ++i) {
					p_effect->setPerfect(i);
				}
			}
			else {
				for (int i = slideLaneIndexEnd; i <= slideLaneIndexStart; ++i) {
					p_effect->setPerfect(i);
				}
			}
		}
		if (1 <= p_keyHitCheck->getHitKeyLong(key)) {
			if (time - Global::GREAT < nowTime + Config::g_judgeCorrection && nowTime + Config::g_judgeCorrection < time + Global::GREAT) {
				setDone(true);
				p_score->plusPerfect();
				p_soundEffect->playSoundEffect();
				if (directionRightOrLeft == 0) {
					for (int i = slideLaneIndexStart; i <= slideLaneIndexEnd; ++i) {
						p_effect->setPerfect(i);
					}
				}
				else {
					for (int i = slideLaneIndexEnd; i <= slideLaneIndexStart; ++i) {
						p_effect->setPerfect(i);
					}
				}
			}
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

void Make::Play::Make_Play_SlideNote::setAuto() {
	if (isAuto) {
		isAuto = false;
	}
	else {
		isAuto = true;
	}
}

void Make::Play::Make_Play_SlideNote::setYUpdateBorder() {
	yUpdateBorderMin = time - 1 / Config::g_hiSpeed;
	yUpdateBorderMax = time - (Global::JUDGELINE_Y - Global::WINDOW_HEIGHT) / (Global::JUDGELINE_Y * Config::g_hiSpeed) + 0.01666;
}

void Make::Play::Make_Play_SlideNote::update(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax) {
		y = Global::JUDGELINE_Y - ((time - nowTime) * Global::JUDGELINE_Y * Config::g_hiSpeed);
		if (turn && time + Global::MISS < nowTime + Config::g_judgeCorrection) {
			setDone(true);
			p_score->plusMiss();
			if (directionRightOrLeft == 0) {
				for (int i = slideLaneIndexStart; i <= slideLaneIndexEnd; ++i) {
					p_effect->setMiss(i);
				}
			}
			else {
				for (int i = slideLaneIndexEnd; i <= slideLaneIndexStart; ++i) {
					p_effect->setMiss(i);
				}
			}
		}
	}
}

void Make::Play::Make_Play_SlideNote::updateKey() {
	if (rightOrLeft == 0 && directionRightOrLeft == 0) {
		key = ::Config::g_laneRR;
	}
	else if (rightOrLeft == 0 && directionRightOrLeft == 1) {
		key = ::Config::g_laneRL;
	}
	else if (rightOrLeft == 1 && directionRightOrLeft == 0) {
		key = ::Config::g_laneLR;
	}
	else if (rightOrLeft == 1 && directionRightOrLeft == 1) {
		key = ::Config::g_laneLL;
	}
}

void Make::Play::Make_Play_SlideNote::drawLine() {
	if (directionRightOrLeft == 0) {
		if (rightOrLeft == 0) {
			DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorRR, 3);
		}
		else {
			DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorLR, 3);
		}
	}
	else {
		if (rightOrLeft == 0) {
			DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorRL, 3);
		}
		else {
			DrawLineAA(static_cast<float>(laneXStart), static_cast<float>(y), static_cast<float>(laneXEnd), static_cast<float>(y), colorLL, 3);
		}
	}
}

void Make::Play::Make_Play_SlideNote::drawArrow() {
	if (directionRightOrLeft == 0) {
		for (int i = 0, iSize = slideLaneIndexEnd - slideLaneIndexStart + 1; i < iSize; ++i) {
			for (int k = 0, kSize = Global::ARROW_NUM_LANE; k < kSize; ++k) {
				if (rightOrLeft == 0) {
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorRR, 3);
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorRR, 3);
				}
				else {
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorLR, 3);
					DrawLineAA(static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd - laneWidth * i - arrowWidthBetween * k - Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorLR, 3);
				}
			}
		}
	}
	else {
		for (int i = 0, iSize = slideLaneIndexStart - slideLaneIndexEnd + 1; i < iSize; ++i) {
			for (int k = 0, kSize = Global::ARROW_NUM_LANE; k < kSize; ++k) {
				if (rightOrLeft == 0) {
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorRL, 3);
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorRL, 3);
				}
				else {
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y + Global::ARROW_LENGTH), colorLL, 3);
					DrawLineAA(static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k), static_cast<float>(y),
						static_cast<float>(laneXEnd + laneWidth * i + arrowWidthBetween * k + Global::ARROW_HEIGHT), static_cast<float>(y - Global::ARROW_LENGTH), colorLL, 3);
				}
			}
		}
	}
}

void Make::Play::Make_Play_SlideNote::draw(double nowTime) {
	if (yUpdateBorderMin < nowTime && nowTime < yUpdateBorderMax && !done) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		drawLine();
		drawArrow();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
