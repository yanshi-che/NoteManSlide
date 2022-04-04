#pragma once

#include <memory>
#include <windows.h>

#include "Task.h"
#include "SceneChanger.h"
#include "Make_DrawManager.h"
#include "Singleton_KeyHitCheck.h"
#include "Game_MusicDataShareBetweenOtherSection.h"
#include "Game_PlayResultShare.h"
#include "Game_Home_Home.h"
#include "Game_Menu_MenuManager.h"
#include "Game_Play_PlayManager.h"
#include "Game_Result_Result.h"
#include "Game_Config_Config.h"

class MainSceneManager
{
private:
	Singleton::Singleton_KeyHitCheck* p_keyCheck;
	std::shared_ptr<SceneChanger> p_sceneChanger;
	std::shared_ptr<Game::Game_MusicDataShareBetweenOtherSection> p_musicDataShare;
	std::shared_ptr<Game::Game_PlayResultShare> p_playResultShare;
	Task* scene;
	const int backImgHandle;
	const int bgmHandle;
	bool isPlaying;
public:
	MainSceneManager(const int backImgHandle, const int bgmHandle);
	void initialize();
	void finalize();
	void update();
	void draw();
};

