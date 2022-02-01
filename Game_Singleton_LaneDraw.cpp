#include "Game_Singleton_LaneDraw.h"


Game::Singleton::Game_Singleton_LaneDraw* Game::Singleton::Game_Singleton_LaneDraw::p_instance = nullptr;

Game::Singleton::Game_Singleton_LaneDraw* Game::Singleton::Game_Singleton_LaneDraw::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Game_Singleton_LaneDraw();
	}
	return p_instance;
}

void Game::Singleton::Game_Singleton_LaneDraw::destroyInstance() {
	delete p_instance;
}

void Game::Singleton::Game_Singleton_LaneDraw::draw() {
	if (amountOfLane != NULL) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		for (int i = 0; i <= amountOfLane; i++) {
			DrawLine(laneWidth * i + Global::DRAW_X_MIN, 0, laneWidth * i + Global::DRAW_X_MIN, Global::WINDOW_HEIGHT, laneColor, laneThickness);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

Game::Singleton::Game_Singleton_LaneDraw::Game_Singleton_LaneDraw() :
	laneColor(GetColor(255, 255, 255)),laneThickness(2) {
	amountOfLane = NULL;
	laneWidth = 0;
}

void Game::Singleton::Game_Singleton_LaneDraw::setamountOfLane(std::uint8_t num) {
	amountOfLane = num;
	laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
}