#include "Make_Singleton_LaneDraw.h"


Make::Singleton::Make_Singleton_LaneDraw* Make::Singleton::Make_Singleton_LaneDraw::p_instance = nullptr;

Make::Singleton::Make_Singleton_LaneDraw* Make::Singleton::Make_Singleton_LaneDraw::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_LaneDraw();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_LaneDraw::destroyInstance() {
	delete p_instance;
}

void Make::Singleton::Make_Singleton_LaneDraw::draw() {
	if (amountOfLane != NULL) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
		for (int i = 0; i <= amountOfLane; i++) {
			DrawLineAA(laneWidth * i + Global::DRAW_X_MIN, 0, laneWidth * i + Global::DRAW_X_MIN, Global::WINDOW_HEIGHT, laneColor, laneThickness);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

Make::Singleton::Make_Singleton_LaneDraw::Make_Singleton_LaneDraw() :
	laneColor(GetColor(255, 255, 255)),laneThickness(2) {
	amountOfLane = NULL;
	laneWidth = 0;
}

void Make::Singleton::Make_Singleton_LaneDraw::setamountOfLane(std::uint8_t num) {
	amountOfLane = num;
	laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
}