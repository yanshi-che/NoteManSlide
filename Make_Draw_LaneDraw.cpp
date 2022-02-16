#include "Make_Draw_LaneDraw.h"

Make::Singleton::Make_Draw_LaneDraw::Make_Draw_LaneDraw() :
	laneColor(GetColor(255, 255, 255)),laneThickness(2) {
	amountOfLane = NULL;
	laneWidth = 0;
}

void Make::Singleton::Make_Draw_LaneDraw::draw() {
	if (amountOfLane != NULL) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
		for (int i = 0; i <= amountOfLane; i++) {
			DrawLineAA(laneWidth * i + Global::DRAW_X_MIN, 0, laneWidth * i + Global::DRAW_X_MIN, Global::WINDOW_HEIGHT, laneColor, laneThickness);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Singleton::Make_Draw_LaneDraw::setamountOfLane(std::uint8_t num) {
	amountOfLane = num;
	laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
}