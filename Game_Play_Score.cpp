#include "Game_Play_Score.h"

Game::Play::Game_Play_Score::Game_Play_Score(int font) {
	this->font = font;
	perfect = 0;
	great = 0;
	miss = 0;
	p = "PERFECT :";
	g = "  GREAT :";
	m = "   MISS :";
	color = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	judge = "";
	judgeColor = GetColor(255, 255, 255);
	blend = 0;
	initFontSize = GetFontSize();
	judgeFontSize = 30;
}

void Game::Play::Game_Play_Score::draw() {
	drawScore();
	drawJudge();
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

void Game::Play::Game_Play_Score::drawScore() {
	DrawStringToHandle(10, 400, p.c_str(), color,font, edgeColor);
	DrawStringToHandle(10, 420, g.c_str(), color,font, edgeColor);
	DrawStringToHandle(10, 440, m.c_str(), color,font, edgeColor);
	DrawFormatStringToHandle(140, 400, color,font, "%d", perfect, edgeColor);
	DrawFormatStringToHandle(140, 420, color, font ,"%d", great, edgeColor);
	DrawFormatStringToHandle(140, 440, color,font, "%d", miss, edgeColor);
}

void Game::Play::Game_Play_Score::plusPerfect() {
	++perfect;
	blend = 200;
	judge = "PERFECT";
	judgeColor = GetColor(235, 120, 211);
}

void Game::Play::Game_Play_Score::plusGreat() {
	++great;
	blend = 200;
	judge = " GREAT";
	judgeColor = GetColor(19, 241, 7);
}

void Game::Play::Game_Play_Score::plusMiss() {
	++miss;
	blend = 200;
	judge = " MISS";
	judgeColor = GetColor(124, 126, 122);
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