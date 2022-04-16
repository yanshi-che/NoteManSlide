#include "Game_Play_Lane.h"

Game::Play::Game_Play_Lane::Game_Play_Lane() {
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
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

void Game::Play::Game_Play_Lane::draw() {
	drawBack();
	drawKeyHitLane();
	drawJudgeLine();
	drawLane();
}

void Game::Play::Game_Play_Lane::drawBack() {
	DrawBoxAA(static_cast<float>(laneX[0]), 0, static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::WINDOW_HEIGHT), backColor, true);
}

void Game::Play::Game_Play_Lane::drawKeyHitLane() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane0)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth), 0, static_cast<float>(laneX[1] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane1)) {
		DrawBoxAA(static_cast<float>(laneX[1] + keyHitLineWidth), 0, static_cast<float>(laneX[2] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane2)) {
		DrawBoxAA(static_cast<float>(laneX[2] + keyHitLineWidth), 0, static_cast<float>(laneX[3] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane3)) {
		DrawBoxAA(static_cast<float>(laneX[3] + keyHitLineWidth), 0, static_cast<float>(laneX[4] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane4)) {
		DrawBoxAA(static_cast<float>(laneX[4] + keyHitLineWidth), 0, static_cast<float>(laneX[5] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_lane5)) {
		DrawBoxAA(static_cast<float>(laneX[5] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_laneRL)) {
		DrawBoxAA(static_cast<float>(laneX[Global::LANE_AMOUNT] + keyHitLineWidth), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth + laneWidth * 0.5), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_laneRR)) {
		DrawBoxAA(static_cast<float>(laneX[Global::LANE_AMOUNT] + keyHitLineWidth + laneWidth * 0.5), 0, static_cast<float>(laneX[Global::LANE_AMOUNT] - keyHitLineWidth + laneWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_laneLR)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth - laneWidth * 0.5), 0, static_cast<float>(laneX[0] - keyHitLineWidth), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	if (0 < p_keyHitCheck->getHitKeyLong(::Config::g_laneLL)) {
		DrawBoxAA(static_cast<float>(laneX[0] + keyHitLineWidth - laneWidth), 0, static_cast<float>(laneX[0] - keyHitLineWidth - laneWidth * 0.5), static_cast<float>(Global::WINDOW_HEIGHT), keyHitColor, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Play::Game_Play_Lane::drawLane() {
	for (int i = 0, iSize = Global::LANE_AMOUNT; i <= iSize; ++i) {
		if (i % 6 != 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		}
		DrawLineAA(static_cast<float>(laneX[i]), 0, static_cast<float>(laneX[i]), static_cast<float>(Global::WINDOW_HEIGHT), laneColor, 2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Game::Play::Game_Play_Lane::drawJudgeLine() {
	//äOòg
	DrawBoxAA(static_cast<float>(laneX[0]), static_cast<float>(Global::JUDGELINE_Y - Global::NOTE_HEIGHT), static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::JUDGELINE_Y + Global::NOTE_HEIGHT), judgeLineColor, false);
	//ì‡ë§
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBoxAA(static_cast<float>(laneX[0]), static_cast<float>(Global::JUDGELINE_Y - Global::NOTE_HEIGHT), static_cast<float>(laneX[Global::LANE_AMOUNT]), static_cast<float>(Global::JUDGELINE_Y + Global::NOTE_HEIGHT), judgeLineColor, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}