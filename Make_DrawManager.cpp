#include "Make_DrawManager.h"

Make::Make_DrawManager::Make_DrawManager() {
	p_beatLine = nullptr;
	p_mouseCheck = nullptr;
}

void Make::Make_DrawManager::initialize(){
	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	p_beatLine = std::make_unique<Draw::Make_Draw_BeatLineManager>();
	p_menu = std::make_unique<Draw::Make_Draw_MenuDraw>(p_beatLine);
}

void Make::Make_DrawManager::finalize() {
	Singleton::Make_Singleton_MouseOperationCheck::destroyInstance();
	p_beatLine.reset();
	p_menu.reset();
}

void Make::Make_DrawManager::update() {

}

void Make::Make_DrawManager::draw() {
	p_mouseCheck->checkMouseClick();
	p_beatLine->draw();
}