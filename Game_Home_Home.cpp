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
	titleFontHandle = CreateFontToHandle("Pristina", 120, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
	optionFontHandle = CreateFontToHandle("Pristina", 50, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Game::Home::Game_Home_Home::finalize() {
	p_sceneChanger.reset();
	DeleteFontToHandle(titleFontHandle);
	DeleteFontToHandle(optionFontHandle);
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
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RETURN) == 1) {
		if (boxCount == 0) {
			p_sceneChanger->changeScene(Scene::GameMenu);
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
	drawKeyConf();
}

void Game::Home::Game_Home_Home::drawOption() {
	DrawStringToHandle(310, 300, "Play", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(270, 400, "NoteEdit", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(285, 500, "Config", fontColor, optionFontHandle, edgeColor);
	DrawStringToHandle(310, 600, "Exit", fontColor, optionFontHandle, edgeColor);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawBox(260, 290 + boxWidth * boxCount, 460, 365 + boxWidth * boxCount, GetColor(255, 255, 255), false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Home::Game_Home_Home::drawTitle() {
	DrawStringToHandle(50, 60, "NoteManSlide", fontColor, titleFontHandle, edgeColor);
}

void Game::Home::Game_Home_Home::drawKeyConf() {
	DrawString(10, 700, "åàíË:enter", fontColor,edgeColor);
	DrawString(10, 720, "ëIë:Å™Å´", fontColor,edgeColor);
}