#include "Game_DrawManager.h"

Game::Game_DrawManager::Game_DrawManager() {
	drawFactory = std::make_unique<Draw::Game_Draw_DrawFactory>();
	rane = nullptr;
	beatLine = nullptr;
}

void Game::Game_DrawManager::initialize(){
	menu.setDrawFactory(drawFactory.get());
	rane = drawFactory->getRaneDrawInstance();
	beatLine = drawFactory->getBeatLineDrawInstance();
}

void Game::Game_DrawManager::finalize() {

}

void Game::Game_DrawManager::update() {

}

void Game::Game_DrawManager::draw() {
	beatLine->draw();
	rane->draw();
}