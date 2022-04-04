#include "Game_Play_Score.h"

Game::Play::Game_Play_Score::Game_Play_Score(int font,std::uint16_t maxChain){
	this->font = font;
	clearGageNum = 0;
	clearGageBoxY = clearGageBoxYMin;
	clearGageNumDiv = 100.0 / static_cast<double>(maxChain) * 2.0;
	gageBoxDiv = static_cast<double>((clearGageBoxYMin - clearGageBoxYMax)) / static_cast<double>(maxChain) * 2.0;
	chain = 0;
	chainStr = "CHAIN :";
	score = 0;
	scoreStr = "SCORE :";
	perfect = 0;
	great = 0;
	miss = 0;
	perfectStr = "PERFECT :";
	greatStr = "  GREAT :";
	missStr = "   MISS :";
	judge = "";
	color = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	judgeColor = GetColor(255, 255, 255);
	clearGageColor = GetColor(72,236,232);
	clearGageClearLineColor = GetColor(239,69,235);
	blend = 0;
	initFontSize = GetFontSize();
	judgeFontSize = 30;
	clearGageFontSize = 10;
}

void Game::Play::Game_Play_Score::draw() {
	drawChain();
	drawJudgeScore();
	drawJudge();
	drawScore();
	drawClearGage();
}

void Game::Play::Game_Play_Score::drawClearGage() {
	//外枠
	DrawBox(clearGageBoxX - 5, clearGageBoxYMin + 5, clearGageBoxX + clearGageBoxXWidth + 5, clearGageBoxYMax - 5, color, true);
	//ゲージ背景
	DrawBox(clearGageBoxX, clearGageBoxYMin, clearGageBoxX + clearGageBoxXWidth , clearGageBoxYMax, GetColor(32,32,32), true);
	//クリアパーセント
	SetFontSize(clearGageFontSize);
	DrawFormatStringF(clearGageBoxX - 40, static_cast<float>(clearGageBoxY),color,"%3.1f",clearGageNum);
	SetFontSize(initFontSize);
	//ゲージ（クリア以下）
	DrawBoxAA(clearGageBoxX, clearGageBoxYMin, clearGageBoxX + clearGageBoxXWidth, static_cast<float>(clearGageBoxY), clearGageColor, true);
	//ゲージ（クリア以上）
	if (clearLineNum <= clearGageNum) {
		DrawBoxAA(clearGageBoxX, clearGageBoxYClearLine, clearGageBoxX + clearGageBoxXWidth, static_cast<float>(clearGageBoxY), clearGageClearLineColor, true);
	}
	//クリアライン
	DrawLine(clearGageBoxX, clearGageBoxYClearLine, clearGageBoxX + clearGageBoxXWidth, clearGageBoxYClearLine, color, 3);
}

void Game::Play::Game_Play_Score::drawChain() {
	DrawStringToHandle(560, 400, chainStr.c_str(), color, font, edgeColor);
	DrawFormatStringToHandle(690, 400, color, font, "%d", chain, edgeColor);
}

void Game::Play::Game_Play_Score::drawJudge() {
	SetFontSize(judgeFontSize);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawStringToHandle(320, 430, judge.c_str(), judgeColor, font , edgeColor);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetFontSize(initFontSize);
	if (blend > 0) {
		blend -= 10;
	}
}

void Game::Play::Game_Play_Score::drawJudgeScore() {
	DrawStringToHandle(10, 400, perfectStr.c_str(), color,font, edgeColor);
	DrawStringToHandle(10, 420, greatStr.c_str(), color,font, edgeColor);
	DrawStringToHandle(10, 440, missStr.c_str(), color,font, edgeColor);
	DrawFormatStringToHandle(150, 400, color,font, "%d", perfect, edgeColor);
	DrawFormatStringToHandle(150, 420, color, font ,"%d", great, edgeColor);
	DrawFormatStringToHandle(150, 440, color,font, "%d", miss, edgeColor);
}

void Game::Play::Game_Play_Score::drawScore() {
	DrawStringToHandle(10, 500, scoreStr.c_str(), color, font, edgeColor);
	DrawFormatStringToHandle(150, 500, color, font, "%d", score, edgeColor);
}

void Game::Play::Game_Play_Score::plusPerfect() {
	++chain;
	score += 2;
	clearGageNum += clearGageNumDiv;
	if (100 < clearGageNum) {
		clearGageNum = 100.0;
	}
	clearGageBoxY -= gageBoxDiv;
	if (clearGageBoxY < 50) {
		clearGageBoxY = 50;
	}
	++perfect;
	blend = 200;
	judge = "PERFECT";
	judgeColor = GetColor(235, 120, 211);
}

void Game::Play::Game_Play_Score::plusGreat() {
	++chain;
	score += 1;
	clearGageNum += clearGageNumDiv * 0.5;
	if (100 < clearGageNum) {
		clearGageNum = 100.0;
	}
	clearGageBoxY -= gageBoxDiv * 0.5;
	if (clearGageBoxY < clearGageBoxYMax) {
		clearGageBoxY = clearGageBoxYMax;
	}
	++great;
	blend = 200;
	judge = " GREAT";
	judgeColor = GetColor(19, 241, 7);
}

void Game::Play::Game_Play_Score::plusMiss() {
	chain = 0;
	clearGageNum -= clearGageNumDiv * 2.0;
	if (clearGageNum < 0) {
		clearGageNum = 0;
	}
	clearGageBoxY += gageBoxDiv * 2.0;
	if (clearGageBoxYMin < clearGageBoxY) {
		clearGageBoxY = clearGageBoxYMin;
	}
	++miss;
	blend = 200;
	judge = " MISS";
	judgeColor = GetColor(124, 126, 122);
}

bool  Game::Play::Game_Play_Score::isClear() {
	if (clearLineNum < clearGageNum) {
		return true;
	}
	return false;
}

std::uint16_t Game::Play::Game_Play_Score::getScore() {
	return score;
}

std::uint16_t Game::Play::Game_Play_Score::getPerfect() {
	return perfect;
}

std::uint16_t Game::Play::Game_Play_Score::getGreat() {
	return great;
}

std::uint16_t Game::Play::Game_Play_Score::getMiss() {
	return miss;
}