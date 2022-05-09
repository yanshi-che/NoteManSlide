#include "Make_DrawManager.h"

Make::Make_DrawManager::Make_DrawManager(std::shared_ptr<SceneChanger>& p_sceneChanger) : Task(p_sceneChanger){
	p_mouseCheck = nullptr;
	drawFunc = nullptr;
	updateFunc = nullptr;
}

void Make::Make_DrawManager::initialize(){
	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	p_menu = std::make_unique<Draw::Make_Draw_MenuDraw>(p_sceneChanger);
	drawFunc = p_menu->getDrawFunc();
	SetUseIMEFlag(true);
}

void Make::Make_DrawManager::finalize() {
	drawFunc = nullptr;
	updateFunc = nullptr;
	p_menu->finalize();
	p_menu.reset();
	Singleton::Make_Singleton_MouseOperationCheck::destroyInstance();
	SetUseIMEFlag(false);
}

void Make::Make_DrawManager::update() {
	if (p_menu->getDrawFunc() != nullptr) {
		drawFunc = p_menu->getDrawFunc();
		p_menu->resetDrawFunc();
	}
	if (p_menu->checkUpdateFunc()) {
		updateFunc = p_menu->getUpdateFunc();
		p_menu->resetUpdateFunc();
	}
	p_mouseCheck->checkMouseClick();
	if (updateFunc != nullptr) {
		updateFunc();
	}
}

void Make::Make_DrawManager::draw() {
	drawFunc();
}