#include "Make_Draw_LaneDraw.h"

Make::Draw::Make_Draw_LaneDraw::Make_Draw_LaneDraw() :
	laneColor(GetColor(255, 255, 255)),backColor(GetColor(0,0,0)),laneThickness(2) {
	laneAmount = Global::LANE_AMOUNT;
	laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
}

void Make::Draw::Make_Draw_LaneDraw::draw() {
	DrawBoxAA(Global::DRAW_X_MIN,0, Global::DRAW_X_MAX, Global::WINDOW_HEIGHT,backColor,true);
	for (int i = 0; i <= laneAmount; i++) {
		if (i % 6 != 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		}
		DrawLineAA(static_cast<float>(laneWidth * i + Global::DRAW_X_MIN), 0, static_cast<float>(laneWidth * i + Global::DRAW_X_MIN), Global::WINDOW_HEIGHT, laneColor, laneThickness);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}