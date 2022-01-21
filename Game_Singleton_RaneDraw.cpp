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

void Game::Singleton::Game_Singleton_RaneDraw::setNumberOfRane(std::uint8_t num) {
	numberOfRane = num;
	raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / numberOfRane;
}