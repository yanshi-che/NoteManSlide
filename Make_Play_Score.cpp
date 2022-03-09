#include "Make_Play_Score.h"

Make::Play::Make_Play_Score::Make_Play_Score() {
	perfect = 0;
	great = 0;
	miss = 0;
	p = "PERFECT :";
	g = "  GREAT :";
	m = "   MISS :";
	color = GetColor(255, 255, 255);
	judge = "";
	judgeColor = GetColor(255, 255, 255);
	blend = 0;
	initFontSize = GetFontSize();
	judgeFontSize = 30;
}

void Make::Play::Make_Play_Score::draw() {
	drawScore();
	drawJudge();
}

void Make::Play::Make_Play_Score::drawJudge() {
	SetFontSize(judgeFontSize);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawStringF(320, 430, judge.c_str(), judgeColor,color);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetFontSize(initFontSize);
	if (blend > 0) {
		blend -= 10;
	}
}

void Make::Play::Make_Play_Score::drawScore() {
	DrawStringF(10, 400, p.c_str(), color);
	DrawStringF(10, 420, g.c_str(), color);
	DrawStringF(10, 440, m.c_str(), color);
	DrawFormatStringF(100, 400, color, "%d", perfect);
	DrawFormatStringF(100, 420, color, "%d", great);
	DrawFormatStringF(100, 440, color, "%d", miss);
}

void Make::Play::Make_Play_Score::plusPerfect() {
	++perfect;
	blend = 200;
	judge = "PERFECT";
	judgeColor = GetColor(235,120,211);
}

void Make::Play::Make_Play_Score::plusGreat() {
	++great;
	blend = 200;
	judge = " GREAT";
	judgeColor = GetColor(19, 241, 7);
}

void Make::Play::Make_Play_Score::plusMiss() {
	++miss;
	blend = 200;
	judge = " MISS";
	judgeColor = GetColor(124, 126, 122);
}

void Make::Play::Make_Play_Score::minusPerfect() {
	--perfect;
}

void Make::Play::Make_Play_Score::minusGreat() {
	--great;
}

void Make::Play::Make_Play_Score::minusMiss() {
	--miss;
}

void Make::Play::Make_Play_Score::resetScore() {
	perfect = 0;
	great = 0;
	miss = 0;
}