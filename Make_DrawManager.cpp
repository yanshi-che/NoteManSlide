#include "Make_DrawManager.h"

Make::Make_DrawManager::Make_DrawManager() {
	p_lane = nullptr;
	p_beatLine = nullptr;
	p_mouseCheck = nullptr;
}

void Make::Make_DrawManager::initialize(){
	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	p_lane = Singleton::Make_Singleton_LaneDraw::getInstance();
	p_beatLine = Singleton::Make_Singleton_BeatLineManager::getInstance();
}

void Make::Make_DrawManager::finalize() {

}

void Make::Make_DrawManager::update() {

}

void Make::Make_DrawManager::draw() {
	p_mouseCheck->checkMouseClick();
	p_beatLine->draw();
	p_lane->draw();
}