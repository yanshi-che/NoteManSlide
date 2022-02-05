#include "Game_Singleton_MouseOperationCheck.h"

Game::Singleton::Game_Singleton_MouseOperationCheck*  Game::Singleton::Game_Singleton_MouseOperationCheck::p_instance = nullptr;

Game::Singleton::Game_Singleton_MouseOperationCheck::Game_Singleton_MouseOperationCheck() {
	mouseX = 0;
	mouseY = 0;
	logType = 0;
	button = 0;
}

Game::Singleton::Game_Singleton_MouseOperationCheck* Game::Singleton::Game_Singleton_MouseOperationCheck::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Game_Singleton_MouseOperationCheck();
	}
	return p_instance;
}

void Game::Singleton::Game_Singleton_MouseOperationCheck::destroyInstance() {
	delete p_instance;
}

bool  Game::Singleton::Game_Singleton_MouseOperationCheck::isMouseClickLeftDown() {
	if (GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		logType == MOUSE_INPUT_LOG_DOWN &&
		button == MOUSE_INPUT_LEFT) {
		return true;
	}
	return false;
}

bool Game::Singleton::Game_Singleton_MouseOperationCheck::isMouseClickLeftUp() {
	if (GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		logType == MOUSE_INPUT_LOG_UP &&
		button == MOUSE_INPUT_LEFT) {
		return true;
	}
	return false;
}