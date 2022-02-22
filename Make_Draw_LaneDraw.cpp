#include "Make_Draw_LaneDraw.h"

Make::Draw::Make_Draw_LaneDraw::Make_Draw_LaneDraw() :
	laneColor(GetColor(255, 255, 255)),laneThickness(2) {
	laneAmount = Global::LANEAMOUNT;
	laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
}

void Make::Draw::Make_Draw_LaneDraw::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
	for (int i = 0; i <= laneAmount; i++) {
		DrawLineAA(laneWidth * i + Global::DRAW_X_MIN, 0, laneWidth * i + Global::DRAW_X_MIN, Global::WINDOW_HEIGHT, laneColor, laneThickness);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}