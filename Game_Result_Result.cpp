#include "Game_Result_Result.h"

Game::Result::Game_Result_Result::Game_Result_Result(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare) :Task(p_sceneChanger) {
	p_keyHitCheck = Singleton::Singleton_KeyHitCheck::getInstance();
	perfect = p_playResultShare->getPerfect();
	great = p_playResultShare->getGreat();
	miss = p_playResultShare->getMiss();
	font = 0;
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
}

void Game::Result::Game_Result_Result::initialize() {
	font = CreateFontToHandle("Pristina", 60, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Game::Result::Game_Result_Result::finalize() {
	DeleteFontToHandle(font);
}

void Game::Result::Game_Result_Result::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RETURN) == 1) {
		p_sceneChanger->changeScene(Scene::GameMenu);
	}
}

void Game::Result::Game_Result_Result::draw() {
	DrawStringToHandle(50, 120, "Result", fontColor, font, edgeColor);
	DrawStringToHandle(50, 220, "Perfect :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(250, 220,fontColor, font,"%d",perfect, edgeColor);
	DrawStringToHandle(50, 320, "  Great :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(250, 320, fontColor, font, "%d", great, edgeColor);
	DrawStringToHandle(50, 420, "   Miss :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(250, 420, fontColor, font, "%d", miss, edgeColor);
	DrawString(10, 700, "ÉÅÉjÉÖÅ[Ç÷:enter", fontColor, edgeColor);
}