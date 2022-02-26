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
	drawKeyInfo();
}

void Make::Play::Make_Play_Lane::drawBack() {
	DrawBoxAA(static_cast<float>(laneX[0]), 0, static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::WINDOW_HEIGHT), backColor,true);
}

void Make::Play::Make_Play_Lane::drawKeyHitLane() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane0)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth), 0, static_cast<float>(laneX[1] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane1)) {
		DrawBoxAA(static_cast<float>(laneX[1] + keyHitLineWidth), 0, static_cast<float>(laneX[2] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane2)) {
		DrawBoxAA(static_cast<float>(laneX[2] + keyHitLineWidth), 0, static_cast<float>(laneX[3] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane3)) {
		DrawBoxAA(static_cast<float>(laneX[3] + keyHitLineWidth), 0, static_cast<float>(laneX[4] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane4)) {
		DrawBoxAA(static_cast<float>(laneX[4] + keyHitLineWidth), 0, static_cast<float>(laneX[5] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_lane5)) {
		DrawBoxAA(static_cast<float>(laneX[5] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_laneRL)) {
		DrawBoxAA(static_cast<float>(laneX[Global::LANE_AMOUNT] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth + laneWidth * 0.5), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if ( 0 < p_keyHitCheck->getHitKeyForNote(Global::g_laneRR)) {
		DrawBoxAA(static_cast<float>(laneX[Global::LANE_AMOUNT] + keyHitLineWidth + laneWidth * 0.5), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth + laneWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_laneLR)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth - laneWidth * 0.5), 0, static_cast<float>(laneX[0] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyForNote(Global::g_laneLL)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth - laneWidth), 0, static_cast<float>(laneX[0] - keyHitLineWidth - laneWidth * 0.5), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
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

void Make::Play::Make_Play_Lane::drawKeyInfo() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawStringF(static_cast<float>(laneX[0] +laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0),"D",laneColor);
	DrawStringF(static_cast<float>(laneX[1] + laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "F", laneColor);
	DrawStringF(static_cast<float>(laneX[2] + laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "G", laneColor);
	DrawStringF(static_cast<float>(laneX[3] + laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "H", laneColor);
	DrawStringF(static_cast<float>(laneX[4] + laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "J", laneColor);
	DrawStringF(static_cast<float>(laneX[5] + laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "K", laneColor);
	DrawStringF(static_cast<float>(laneX[0] - laneWidth * 0.8), static_cast<float>(Global::JUDGELINE_Y - 40.0), "R\nÅ©", laneColor);
	DrawStringF(static_cast<float>(laneX[0] - laneWidth * 0.333), static_cast<float>(Global::JUDGELINE_Y - 40.0), "T\nÅ®", laneColor);
	DrawStringF(static_cast<float>(laneX[6] + laneWidth * 0.666), static_cast<float>(Global::JUDGELINE_Y - 40.0), "I\nÅ®", laneColor);
	DrawStringF(static_cast<float>(laneX[6] + laneWidth * 0.2), static_cast<float>(Global::JUDGELINE_Y - 40.0), "U\nÅ©", laneColor);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}