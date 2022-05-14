#include "Game_Result_Result.h"

Game::Result::Game_Result_Result::Game_Result_Result(std::shared_ptr<SceneChanger>& p_sceneChanger,const std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare,const std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare) :Task(p_sceneChanger),p_musicDataShare(p_musicDataShare),p_playResultShare(p_playResultShare) {
	p_keyHitCheck = Singleton::Singleton_KeyHitCheck::getInstance();
	perfect = p_playResultShare->getPerfect();
	great = p_playResultShare->getGreat();
	miss = p_playResultShare->getMiss();
	isPlayToEnd = p_playResultShare->getIsPlayToEnd();
	isClear = p_playResultShare->getIsClear();
	score = p_playResultShare->getScore();
	clearStr = "Failed...";
	font = 0;
	jisFont = 0;
	titleFont = 0;
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
}

void Game::Result::Game_Result_Result::saveData() {
	bool isPerfect = false;
	bool isFullChain = false;
	if (isPlayToEnd) {
		if (isClear) {
			clearStr = "Clear";
		}
		if (miss == NULL) {
			isFullChain = true;
			clearStr = "FullChain";
			if (great == NULL) {
				isPerfect = true;
				clearStr = "PerfectFullChain";
			}
		}
	}
	Menu::Game_Menu_FileOperator fo;
	fo.saveResultData(isPerfect, isFullChain, isClear, score, p_musicDataShare);
}

void Game::Result::Game_Result_Result::initialize() {
	font = CreateFontToHandle("Pristina", 22, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
	jisFont = CreateFontToHandle("游明朝", 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	titleFont = CreateFontToHandle("Pristina", 50, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
	saveData();
}

void Game::Result::Game_Result_Result::finalize() {
	DeleteFontToHandle(font);
	DeleteFontToHandle(jisFont);
	DeleteFontToHandle(titleFont);
}

void Game::Result::Game_Result_Result::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RETURN) == 1) {
		p_sceneChanger->changeScene(Scene::GameMenu);
	}
}

void Game::Result::Game_Result_Result::draw() {
	//背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 196);
	DrawBox(20, 170, 720, 570, GetColor(32, 32, 32), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//タイトル
	DrawStringToHandle(50, 180, "Result", fontColor, titleFont, edgeColor);
	//曲情報
	DrawStringToHandle(50, 260, "  name :", fontColor, font, edgeColor);
	DrawStringToHandle(120, 260, p_musicDataShare->getMusicData()->getName().c_str(), fontColor, jisFont);
	DrawStringToHandle(50, 300, "artist :", fontColor, font, edgeColor);
	DrawStringToHandle(120, 300, p_musicDataShare->getMusicData()->getArtist().c_str(), fontColor, jisFont);
	//レベル
	DrawStringToHandle(460, 280, "level :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(520, 280, fontColor, font, "%d", p_musicDataShare->getMusicData()->getLevel(), edgeColor);
	//スコア
	DrawStringToHandle(50, 360, "Score :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(200, 360, fontColor, font, "%d", score, edgeColor);
	//判定
	DrawStringToHandle(50, 440, "Perfect :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(200, 440, fontColor, font, "%d", perfect, edgeColor);
	DrawStringToHandle(50, 460, "  great :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(200, 460, fontColor, font, "%d", great, edgeColor);
	DrawStringToHandle(50, 480, "   Miss :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(200, 480, fontColor, font, "%d", miss, edgeColor);
	//クリア状況
	DrawStringToHandle(330, 400, clearStr.c_str(), fontColor, titleFont, edgeColor);

	DrawString(10, 700, "メニューへ:enter", fontColor, edgeColor);
}