#include "Make_Play_BarLine.h"

Make::Play::Make_Play_BarLine::Make_Play_BarLine(const double time) :
time(time){
	y = 0;
	color = GetColor(255, 255, 255);
}

void Make::Play::Make_Play_BarLine::update(double nowTime) {
	y = Global::JUDGELINE_Y - ((time - nowTime) * Global::JUDGELINE_Y * Global::g_hiSpeed);
}

void Make::Play::Make_Play_BarLine::draw() {
	if (0 < y && y < Global::WINDOW_HEIGHT) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawLineAA(static_cast<float>(Global::PLAY_LANE_X_MIN), static_cast<float>(y), static_cast<float>(Global::PLAY_LANE_X_MAX), static_cast<float>(y), color);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}