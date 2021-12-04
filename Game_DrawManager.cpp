#include "Game_DrawManager.h"

Game::Game_DrawManager::Game_DrawManager() {
	rane = nullptr;
	beatLine = nullptr;
}

void Game::Game_DrawManager::initialize(){
	rane = drawFactory.getRaneDrawInstance();
	beatLine = drawFactory.getBeatLineDrawInstance();
}

void Game::Game_DrawManager::finalize() {

}

void Game::Game_DrawManager::update() {

}

void Game::Game_DrawManager::draw() {
	rane->draw();
	beatLine->draw();
}