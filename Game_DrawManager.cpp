#include "Game_DrawManager.h"

Game::Game_DrawManager::Game_DrawManager() {
	rane = nullptr;
	beatLine = nullptr;
}

void Game::Game_DrawManager::initialize(){
	rane = Singleton::Game_Singleton_RaneDraw::getInstance();
	beatLine = Singleton::Game_Singleton_BeatLineDraw::getInstance();
}

void Game::Game_DrawManager::finalize() {

}

void Game::Game_DrawManager::update() {

}

void Game::Game_DrawManager::draw() {
	beatLine->draw();
	rane->draw();
}