#pragma once

#include <memory>
#include <windows.h>

#include "Task.h"
#include "SceneChanger.h"
#include "Make_DrawManager.h"
#include "Singleton_KeyHitCheck.h"
#include "Game_Home_Home.h"

class MainSceneManager
{
private:
	Singleton::Singleton_KeyHitCheck* p_keyCheck;
	std::shared_ptr<SceneChanger> p_sceneChanger;
	Task* scene;
public:
	MainSceneManager();
	void initialize();
	void finalize();
	void update();
	void draw();
};

