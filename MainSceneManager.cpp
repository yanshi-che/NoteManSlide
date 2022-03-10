#include "MainSceneManager.h"

MainSceneManager::MainSceneManager() {
	p_sceneChanger = std::make_shared<SceneChanger>();
	p_keyCheck = Singleton::Singleton_KeyHitCheck::getInstance();
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
		}else if(p_sceneChanger->getNextScene() == Scene::NoteEdit) {
			scene = static_cast<Task*>(new Make::Make_DrawManager(p_sceneChanger));
		}
		else if (p_sceneChanger->getNextScene() == Scene::Exit) {
			SendMessage(GetMainWindowHandle(),WM_CLOSE,NULL,NULL);
			return;
		}
		p_sceneChanger->changeScene(Scene::None);
		scene->initialize();
	}
	p_keyCheck->checkHitKey();
	scene->update();
}

void MainSceneManager::MainSceneManager::draw() {
	if (scene != nullptr) {
		scene->draw();
	}
}