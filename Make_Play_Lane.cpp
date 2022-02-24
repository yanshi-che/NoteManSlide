#include "Make_Play_Lane.h"

Make::Play::Make_Play_Lane::Make_Play_Lane() {
	p_keyHitCheck = Singleton::Make_Singleton_KeyHitCheck::getInstance();
	//ÉåÅ[ÉìÇÃÇòç¿ïW
	laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / Global::LANE_AMOUNT;
	for (int i = 0; i <= Global::LANE_AMOUNT; ++i) {
		laneX[i] = laneWidth * i + Global::PLAY_LANE_X_MIN;
	}
	laneColor = GetColor(255, 255, 255);
	backColor = GetColor(0, 0, 0);
	judgeLineColor = GetColor(255, 0, 0);
	keyHitColor = GetColor(83, 249, 244);
}

void Make::Play::Make_Play_Lane::draw() {
	drawBack();
	drawKeyHitLane();
	drawJudgeLine();
	drawLane();
	drawDown();
}

void Make::Play::Make_Play_Lane::drawBack() {
	DrawBoxAA(static_cast<float>(laneX[0]), 0, static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::WINDOW_HEIGHT), backColor,true);
}

void Make::Play::Make_Play_Lane::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(laneX[0] + 1), static_cast<float>(Global::JUDGELINE_Y + 1.0), static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::WINDOW_HEIGHT), backColor,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_Lane::drawKeyHitLane() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
	if (0 < p_keyHitCheck->getHitKey(Global::lane0)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth), 0, static_cast<float>(laneX[1] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::lane1)) {
		DrawBoxAA(static_cast<float>(laneX[1] + keyHitLineWidth), 0, static_cast<float>(laneX[2] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::lane2)) {
		DrawBoxAA(static_cast<float>(laneX[2] + keyHitLineWidth), 0, static_cast<float>(laneX[3] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::lane3)) {
		DrawBoxAA(static_cast<float>(laneX[3] + keyHitLineWidth), 0, static_cast<float>(laneX[4] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::lane4)) {
		DrawBoxAA(static_cast<float>(laneX[4] + keyHitLineWidth), 0, static_cast<float>(laneX[5] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::lane5)) {
		DrawBoxAA(static_cast<float>(laneX[5] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::laneRR) || 0 < p_keyHitCheck->getHitKey(Global::laneRL)) {
		DrawBoxAA(static_cast<float>(laneX[Global::LANE_AMOUNT] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth + laneWidth * 0.3), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKey(Global::laneLR) || 0 < p_keyHitCheck->getHitKey(Global::laneLL)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth - laneWidth * 0.3), 0, static_cast<float>(laneX[0] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_Lane::drawLane() {
	for (int i = 0, iSize = Global::LANE_AMOUNT; i <= iSize; ++i) {
		if (i % 6 != 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		}
		DrawLineAA(static_cast<float>(laneX[i]), 0, static_cast<float>(laneX[i]), static_cast<float>(Global::WINDOW_HEIGHT), laneColor ,2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Play::Make_Play_Lane::drawJudgeLine() {
	DrawLineAA(static_cast<float>(laneX[0]), static_cast<float>(Global::JUDGELINE_Y), static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::JUDGELINE_Y), judgeLineColor,5);
}