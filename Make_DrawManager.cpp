#include "Make_DrawManager.h"

Make::Make_DrawManager::Make_DrawManager(std::shared_ptr<SceneChanger>& p_sceneChanger) : Task(p_sceneChanger){
	p_mouseCheck = nullptr;
	drawFunc = nullptr;
}

void Make::Make_DrawManager::initialize(){
	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	p_menu = std::make_unique<Draw::Make_Draw_MenuDraw>(p_sceneChanger);
	drawFunc = p_menu->getDrawFunc();
}

void Make::Make_DrawManager::finalize() {
	drawFunc = nullptr;
	p_menu->finalize();
	p_menu.reset();
	Singleton::Make_Singleton_MouseOperationCheck::destroyInstance();
}

void Make::Make_DrawManager::update() {
	if (p_menu->getDrawFunc() != nullptr) {
		drawFunc = p_menu->getDrawFunc();
		p_menu->resetDrawFunc();
	}
}

void Make::Make_DrawManager::draw() {
	p_mouseCheck->checkMouseClick();
	drawFunc();
}