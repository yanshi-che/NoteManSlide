#include "MainSceneManager.h"

MainSceneManager::MainSceneManager(const int backImgHandle, const int bgmHandle) : backImgHandle(backImgHandle),bgmHandle(bgmHandle){
	p_sceneChanger = std::make_shared<SceneChanger>();
	p_musicDataShare = std::make_shared<Game::Game_MusicDataShareBetweenMenuAndPlay>();
	p_playResultShare = std::make_shared<Game::Game_PlayResultShare>();
	p_keyCheck = Singleton::Singleton_KeyHitCheck::getInstance();
	isPlaying = false;
	scene = static_cast<Task*>(new Game::Home::Game_Home_Home(p_sceneChanger));
}

void MainSceneManager::MainSceneManager::initialize() {
	scene->initialize();
}

void MainSceneManager::MainSceneManager::finalize() {
	if (scene != nullptr) {
		scene->finalize();
	}
}

void MainSceneManager::MainSceneManager::update() {
	if (p_sceneChanger->getNextScene() != Scene::None) {
		scene->finalize();
		delete scene;
		scene = nullptr;
		if (p_sceneChanger->getNextScene() == Scene::Home) {
			scene = static_cast<Task*>(new Game::Home::Game_Home_Home(p_sceneChanger));
		}else if(p_sceneChanger->getNextScene() == Scene::GameMenu) {
			scene = static_cast<Task*>(new Game::Menu::Game_Menu_MenuManager(p_sceneChanger,p_musicDataShare));
		}
		else if (p_sceneChanger->getNextScene() == Scene::NoteEdit) {
			scene = static_cast<Task*>(new Make::Make_DrawManager(p_sceneChanger));
		}
		else if(p_sceneChanger->getNextScene() == Scene::GamePlay) {
			StopSoundMem(bgmHandle);
			isPlaying = true;
			scene = static_cast<Task*>(new Game::Play::Game_Play_PlayManager(p_sceneChanger,p_musicDataShare,p_playResultShare));
		}
		else if (p_sceneChanger->getNextScene() == Scene::GameResult) {
			isPlaying = false;
			scene = static_cast<Task*>(new Game::Result::Game_Result_Result(p_sceneChanger,p_playResultShare));
		}
		else if (p_sceneChanger->getNextScene() == Scene::Config) {
			scene = static_cast<Task*>(new Game::Config::Game_Config_Config(p_sceneChanger));
		}
		else if (p_sceneChanger->getNextScene() == Scene::Exit) {
			SendMessage(GetMainWindowHandle(),WM_CLOSE,NULL,NULL);
			return;
		}
		p_sceneChanger->changeScene(Scene::None);
		scene->initialize();
	}
	if (!isPlaying && CheckSoundMem(bgmHandle) != 1) {
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, true);
	}
	p_keyCheck->checkHitKey();
	scene->update();
}

void MainSceneManager::MainSceneManager::draw() {
	DrawGraph(0, 0, backImgHandle, false);
	if (scene != nullptr) {
		scene->draw();
	}
}