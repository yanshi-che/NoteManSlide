#include "Game_Play_Effect.h"

Game::Play::Game_Play_Effect::Game_Play_Effect() {
	//ÉåÅ[ÉìÇÃÇòç¿ïW
	for (int i = 0; i < effectHandleSize; ++i) {
		perfectEffectHandle[i] = 0;
		greatEffectHandle[i] = 0;
		missEffectHandle[i] = 0;
	}
	double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / Global::LANE_AMOUNT;
	for (int i = 0; i < Global::LANE_AMOUNT; ++i) {
		laneX[i] = laneWidth * i + Global::PLAY_LANE_X_MIN - 30;
		for (int k = 0; k < 3; ++k) {
			isEffect[i][k] = false;
			effectCount[i][k] = 0;
		}
	}

}

bool Game::Play::Game_Play_Effect::loadEffect() {
	try {
		LoadDivGraph(".\\image\\effect\\perfect.png", 15, 5, 3, 120, 120, perfectEffectHandle);
		LoadDivGraph(".\\image\\effect\\great.png", 15, 5, 3, 120, 120, greatEffectHandle);
		LoadDivGraph(".\\image\\effect\\miss.png", 15, 5, 3, 120, 120, missEffectHandle);
	}
	catch (...) {
		return false;
	}
	return true;
}

void Game::Play::Game_Play_Effect::finalize() {
	for (int i = 0; i < effectHandleSize; ++i) {
		DeleteGraph(perfectEffectHandle[i]);
		DeleteGraph(greatEffectHandle[i]);
		DeleteGraph(missEffectHandle[i]);
	}
}

void Game::Play::Game_Play_Effect::setPerfect(std::uint16_t laneIndex) {
	isEffect[laneIndex][0] = true;
	effectCount[laneIndex][0] = 0;
}

void Game::Play::Game_Play_Effect::setGreat(std::uint16_t laneIndex) {
	isEffect[laneIndex][1] = true;
	effectCount[laneIndex][1] = 0;
}

void Game::Play::Game_Play_Effect::setMiss(std::uint16_t laneIndex) {
	isEffect[laneIndex][2] = true;
	effectCount[laneIndex][2] = 0;
}

void Game::Play::Game_Play_Effect::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		if (isEffect[i][0]) {
			DrawGraphF(static_cast<float>(laneX[i]), Global::JUDGELINE_Y - 60, perfectEffectHandle[effectCount[i][0]], true);
			++effectCount[i][0];
			if (effectCount[i][0] == 15) {
				isEffect[i][0] = false;
			}
		}
		if (isEffect[i][1]) {
			DrawGraphF(static_cast<float>(laneX[i]), Global::JUDGELINE_Y - 60, greatEffectHandle[effectCount[i][1]], true);
			++effectCount[i][1];
			if (effectCount[i][1] == 15) {
				isEffect[i][1] = false;
			}
		}
		if (isEffect[i][2]) {
			DrawGraphF(static_cast<float>(laneX[i]), Global::JUDGELINE_Y - 60, missEffectHandle[effectCount[i][2]], true);
			++effectCount[i][2];
			if (effectCount[i][2] == 15) {
				isEffect[i][2] = false;
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}