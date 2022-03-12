#pragma once

#include <memory>
#include <windows.h>

#include "Task.h"
#include "SceneChanger.h"
#include "Make_DrawManager.h"
#include "Singleton_KeyHitCheck.h"
#include "Game_Home_Home.h"
#include "Game_Menu_MenuManager.h"

class MainSceneManager
{
private:
	Singleton::Singleton_KeyHitCheck* p_keyCheck;
	std::shared_ptr<SceneChanger> p_sceneChanger;
	Task* scene;
	const int backImgHandle;
public:
	MainSceneManager(const int backImgHandle);
	void initialize();
	void finalize();
	void update();
	void draw();
};

