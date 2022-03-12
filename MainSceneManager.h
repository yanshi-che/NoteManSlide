#pragma once

#include <memory>
#include <windows.h>

#include "Task.h"
#include "SceneChanger.h"
#include "Make_DrawManager.h"
#include "Singleton_KeyHitCheck.h"
#include "Game_Home_Home.h"
#include "Game_Menu_MenuManager.h"
#include "Game_MusicDataShareBetweenMenuAndPlay.h"
#include "Game_Play_PlayManager.h"

class MainSceneManager
{
private:
	Singleton::Singleton_KeyHitCheck* p_keyCheck;
	std::shared_ptr<SceneChanger> p_sceneChanger;
	std::shared_ptr <Game::Game_MusicDataShareBetweenMenuAndPlay> p_musicDataShare;
	Task* scene;
	const int backImgHandle;
public:
	MainSceneManager(const int backImgHandle);
	void initialize();
	void finalize();
	void update();
	void draw();
};

