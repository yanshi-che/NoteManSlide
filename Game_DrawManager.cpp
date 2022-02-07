#include "Game_DrawManager.h"

Game::Game_DrawManager::Game_DrawManager() {
	p_lane = nullptr;
	p_beatLine = nullptr;
	p_mouseCheck = nullptr;
}

void Game::Game_DrawManager::initialize(){
	p_mouseCheck = Singleton::Game_Singleton_MouseOperationCheck::getInstance();
	p_lane = Singleton::Game_Singleton_LaneDraw::getInstance();
	p_beatLine = Singleton::Game_Singleton_BeatLineManager::getInstance();
}

void Game::Game_DrawManager::finalize() {

}

void Game::Game_DrawManager::update() {

}

void Game::Game_DrawManager::draw() {
	p_mouseCheck->checkMouseClick();
	p_beatLine->draw();
	p_lane->draw();
}