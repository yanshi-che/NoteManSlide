#include "Make_Play_Score.h"

Make::Play::Make_Play_Score::Make_Play_Score() {
	perfect = 0;
	great = 0;
	miss = 0;
	p = "perfect :";
	g = "  great :";
	m = "   miss :";
	color = GetColor(255, 255, 255);
}

void Make::Play::Make_Play_Score::draw() {
	DrawStringF(580, 500, p.c_str(), color);
	DrawStringF(580, 520, g.c_str(), color);
	DrawStringF(580, 540, m.c_str(), color);
	DrawFormatStringF(670, 500, color, "%d", perfect);
	DrawFormatStringF(670, 520, color, "%d", great);
	DrawFormatStringF(670, 540, color, "%d", miss);
}

void Make::Play::Make_Play_Score::plusPerfect() {
	++perfect;
}

void Make::Play::Make_Play_Score::plusGreat() {
	++great;
}

void Make::Play::Make_Play_Score::plusMiss() {
	++miss;
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