#include "Game_Singleton_RaneDraw.h"


Game::Singleton::Game_Singleton_RaneDraw* Game::Singleton::Game_Singleton_RaneDraw::instance = nullptr;

Game::Singleton::Game_Singleton_RaneDraw* Game::Singleton::Game_Singleton_RaneDraw::getInstance() {
	if (instance == nullptr) {
		instance = new Game_Singleton_RaneDraw();
	}
	return instance;
}

void Game::Singleton::Game_Singleton_RaneDraw::destroyInstance() {
	delete instance;
}

Game::Singleton::Game_Singleton_RaneDraw::Game_Singleton_RaneDraw() :
	raneColor(GetColor(255, 255, 255)),raneThickness(2) {
	numberOfRane = NULL;
	raneWidth = 0;
}

void Game::Singleton::Game_Singleton_RaneDraw::draw() noexcept{
	if (numberOfRane != NULL) {
		for (int i = 0; i <= numberOfRane; i++) {
			DrawLine(raneWidth * i + Global::DRAW_X_MIN , 0, raneWidth * i + Global::DRAW_X_MIN , Global::WINDOW_HEIGHT, raneColor, raneThickness);
		}
	}
}

void Game::Singleton::Game_Singleton_RaneDraw::setNumberOfRane(std::uint8_t num) noexcept {
	numberOfRane = num;
	raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / numberOfRane;
}