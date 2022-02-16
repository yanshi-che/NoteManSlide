#include "Make_DrawManager.h"

Make::Make_DrawManager::Make_DrawManager() {
	p_beatLine = nullptr;
	p_mouseCheck = nullptr;
}

void Make::Make_DrawManager::initialize(){
	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	p_beatLine = Singleton::Make_Singleton_BeatLineManager::getInstance();
}

void Make::Make_DrawManager::finalize() {
	Singleton::Make_Singleton_BeatLineManager::destroyInstance();
	Singleton::Make_Singleton_BeatLineManager::destroyInstance();
}

void Make::Make_DrawManager::update() {

}

void Make::Make_DrawManager::draw() {
	p_mouseCheck->checkMouseClick();
	p_beatLine->draw();
}