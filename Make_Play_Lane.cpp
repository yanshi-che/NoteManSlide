#include "Make_Play_Lane.h"

Make::Play::Make_Play_Lane::Make_Play_Lane() {
	//ÉåÅ[ÉìÇÃÇòç¿ïW
	const double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / Global::LANE_AMOUNT;
	for (int i = 0; i <= Global::LANE_AMOUNT; ++i) {
		laneX[i] = laneWidth * i + Global::DRAW_X_MIN;
	}
	laneColor = GetColor(255, 255, 255);
	backColor = GetColor(0, 0, 0);
	judgeLineColor = GetColor(255, 0, 0);
	keyHitColor = GetColor(83, 249, 244);
}

void Make::Play::Make_Play_Lane::draw() {
	drawBack();

	drawJudgeLine();
	drawLane();
	drawDown();
}

void Make::Play::Make_Play_Lane::drawBack() {
	DrawBoxAA(static_cast<float>(laneX[0]), 0, static_cast<float>(laneX[Global::LANE_AMOUNT + 1]), static_cast<float>(Global::WINDOW_HEIGHT), backColor,true);
}

void Make::Play::Make_Play_Lane::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(laneX[0]), static_cast<float>(Global::JUDGELINE_Y + 1.0), static_cast<float>(laneX[Global::LANE_AMOUNT + 1]), static_cast<float>(Global::WINDOW_HEIGHT), backColor,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_Lane::drawKeyHitLane() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_Lane::drawLane() {
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		if (i % 6 != 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		}
		DrawLineAA(static_cast<float>(laneX[i]), 0, static_cast<float>(laneX[i+1]), static_cast<float>(Global::WINDOW_HEIGHT), laneColor);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Play::Make_Play_Lane::drawJudgeLine() {
	DrawLineAA(static_cast<float>(laneX[0]), static_cast<float>(Global::JUDGELINE_Y), static_cast<float>(laneX[Global::LANE_AMOUNT + 1]), static_cast<float>(Global::JUDGELINE_Y), judgeLineColor,3);
}