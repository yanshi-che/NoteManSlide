#include "Game_Home_Home.h"

Game::Home::Game_Home_Home::Game_Home_Home(std::shared_ptr<SceneChanger>& p_sceneChanger) : Task(p_sceneChanger){
	p_keyHitCheck = nullptr;
	titleFontHandle = 0;
	optionFontHandle = 0;
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	boxWidth = 100;
	boxCount = 0;
	blend = 255;
	blendDiff = -5;
}

void Game::Home::Game_Home_Home::initialize() {
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
	titleFontHandle = CreateFontToHandle("Edwardian Script ITC", 120, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
	optionFontHandle = CreateFontToHandle("Edwardian Script ITC", 50, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Game::Home::Game_Home_Home::finalize() {
	DeleteFontToHandle(titleFontHandle);
}

void Game::Home::Game_Home_Home::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP) == 1) {
		--boxCount;
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1) {
		++boxCount;
	}
	if (boxCount < 0) {
		boxCount = 3;
	}
	if (3 < boxCount) {
		boxCount = 0;
	}
	blend += blendDiff;
	if (blend == 0 || blend == 255) {
		blendDiff = -blendDiff;
	}
	if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_RETURN)) {
		if (boxCount == 0) {
			p_sceneChanger->changeScene(Scene::GamePlay);
		}else if(boxCount == 1){
			p_sceneChanger->changeScene(Scene::NoteEdit);
		}
		else if (boxCount == 2) {
			p_sceneChanger->changeScene(Scene::Config);
		}
		else if (boxCount == 3) {
			p_sceneChanger->changeScene(Scene::Exit);
		}
	}
}

void Game::Home::Game_Home_Home::draw() {
	drawTitle();
	drawOption();
}

void Game::Home::Game_Home_Home::drawOption() {
	DrawStringToHandle(305, 300, "Play", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(270, 400, "NoteEdit", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(280, 500, "Config", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(305, 600, "Exit", fontColor, optionFontHandle, edgeColor);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawBox(260, 295 + boxWidth * boxCount, 460, 370 + boxWidth * boxCount, GetColor(255, 255, 255), false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Home::Game_Home_Home::drawTitle() {
	DrawStringToHandle(55, 60, "NoteManSlide", fontColor, titleFontHandle, edgeColor);
}
