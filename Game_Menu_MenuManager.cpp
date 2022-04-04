#include "Game_Menu_MenuManager.h"

Game::Menu::Game_Menu_MenuManager::Game_Menu_MenuManager(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare) :Task(p_sceneChanger), p_musicDataShare(p_musicDataShare) {
	p_keyHitCheck = Singleton::Singleton_KeyHitCheck::getInstance();
	//フォントデータのハンドル
	focusedMusicListFontHandle = 0;
	notFocusedMusicListFontHandle = 0;
	focusedMusicFontHandle = 0;
	difficultyFontHandle = 0;
	//色
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);

	difficultyCount = 0;
	blend = 255;
	blendDiff = -5;

	for (int i = 0; i < difficultyCountBorder; ++i) {
		bestScore[i] = "";
		clearStatus[i] = "";
	}
	bpm = "";
	easyNum = "";
	normalNum = "";
	hardNum = "";

	p_fileOp = nullptr;
	p_focusedMusicData = nullptr;
	isFail = false;
}

void Game::Menu::Game_Menu_MenuManager::initialize() {
	focusedMusicListFontHandle = CreateFontToHandle("Pristina", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	notFocusedMusicListFontHandle = CreateFontToHandle("Pristina", 20, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	focusedMusicFontHandle = CreateFontToHandle("Pristina", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	difficultyFontHandle = CreateFontToHandle("Pristina", 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	p_fileOp = std::make_unique<Game_Menu_FileOperator>();
	if (!p_fileOp->getMusicData(musicDataVec)) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "譜面データまたは音楽ファイルの読み込みに失敗しました。\nディレクトリ構成、またはファイルに問題がある可能性があります。", fontColor, edgeColor);
		DrawString(80, 420, "5秒後にホームに戻ります", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isFail = true;
		p_sceneChanger->changeScene(Scene::Home);
		return;
	}
	for (int i = 0, iSize = static_cast<int>(musicDataVec.size()); i < iSize; ++i) {
		musicDataVecElementDeq.push_back(i);
	}
	p_focusedMusicData = &musicDataVec.at(0);
	setDifficultyFocusedMusicDataStr();
}

void Game::Menu::Game_Menu_MenuManager::finalize() {
	DeleteFontToHandle(focusedMusicListFontHandle);
	DeleteFontToHandle(notFocusedMusicListFontHandle);
	DeleteFontToHandle(focusedMusicFontHandle);
	DeleteFontToHandle(difficultyFontHandle);
	p_fileOp.reset();
	for (int i = 0,iSize= static_cast<int>(p_focusedMusicData->size()); i < iSize; ++i) {
		p_focusedMusicData->at(i).reset();
	}
	for (int i = 0, iSize = static_cast<int>(musicDataVec.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(musicDataVec.at(i).size()); k < kSize; ++k) {
			musicDataVec.at(i).at(k).reset();
		}
	}
}

void Game::Menu::Game_Menu_MenuManager::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP) == 1) {
		setPrevFocusedMusicData();
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1) {
		setNextFocusedMusicData();
	}

	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_LEFT) == 1) {
		difficultyCount = (difficultyCount + 2)  % difficultyCountBorder;
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RIGHT) == 1) {
		difficultyCount = (difficultyCount + 1) % difficultyCountBorder;
	}

	if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_ESCAPE)) {
		p_sceneChanger->changeScene(Scene::Home);
	}

	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RETURN) == 1) {
		p_musicDataShare->setMusicData(p_focusedMusicData->at(difficultyCount));
		p_musicDataShare->setDifficulty(difficultyCount);
		p_sceneChanger->changeScene(Scene::GamePlay);
	}

	blend += blendDiff;
	if (blend == 0 || blend == 255) {
		blendDiff = -blendDiff;
	}
}

void Game::Menu::Game_Menu_MenuManager::draw() {
	if (!isFail) {
		drawKeyConf();
		drawFocusedMusicData();
		drawMusicList();
	}
}

void Game::Menu::Game_Menu_MenuManager::drawMusicList() {
	for (int i = 0; i < musicListSize; ++i) {
		if (i != 3) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 136);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
			DrawBox(115, 245 + i * 70, 635, 285 + i * 70, GetColor(255, 255, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

		DrawBox(120, 250 + i * 70, 630, 280 + i * 70, GetColor(120, 134, 134), true);

		if (i != 3) {
			DrawStringToHandle(125, 255 + i * 70, musicDataVec.at(musicDataVecElementDeq.at((i + 4) % 7)).at(0)->getName().c_str(), fontColor, notFocusedMusicListFontHandle, edgeColor);
		}
		else {
			DrawStringToHandle(125, 255 + i * 70, musicDataVec.at(musicDataVecElementDeq.at((i + 4) % 7)).at(0)->getName().c_str(), fontColor, focusedMusicListFontHandle, edgeColor);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Menu::Game_Menu_MenuManager::drawFocusedMusicData() {
	//背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 196);
	DrawBox(10, 30, 730, 200, GetColor(32, 32, 32), true);
	for (int i = 0; i < 30; ++i) {
		if (i < 10) {
			DrawBox(40 + i, 50 + i, 160 + i, 60 + i, GetColor(134 - i * 5, 134, 134 - i * 5), true);
			DrawBox(200 + i, 50 + i, 400 + i, 60 + i, GetColor(134, 134, 134 - i * 5), true);
			DrawBox(440 + i, 50 + i, 600 + i, 60 + i, GetColor(134, 134 - i * 5, 134 - i * 5), true);
		}
		DrawBox(40 + i, 71 + i, 600 + i, 81 + i, GetColor(134, 134 - i * 2, 134), true);
	}
	//選択されている難易度
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	DrawBox(130 + difficultyCount * 200, 115, 195 + difficultyCount * 200, 195, GetColor(255, 255, 255), false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//BPM
	DrawStringToHandle(50, 50, bpm.c_str(), fontColor, focusedMusicFontHandle,edgeColor);
	//ベストスコア
	DrawStringToHandle(210, 50, bestScore[difficultyCount].c_str(), fontColor, focusedMusicFontHandle, edgeColor);
	// クリア状況
	DrawStringToHandle(450, 50, clearStatus[difficultyCount].c_str(), fontColor, focusedMusicFontHandle, edgeColor);
	//曲名
	DrawStringToHandle(70, 71, p_focusedMusicData->at(0)->getName().c_str(), fontColor, focusedMusicFontHandle, edgeColor);
	//アーティスト
	DrawStringToHandle(70, 91, p_focusedMusicData->at(0)->getArtist().c_str(), fontColor, focusedMusicFontHandle, edgeColor);
	//難易度
	DrawStringToHandle(145, 170, "easy", GetColor(109, 250, 123), focusedMusicFontHandle);
	DrawStringToHandle(140, 120, easyNum.c_str(), fontColor, difficultyFontHandle,edgeColor);
	DrawStringToHandle(335, 170, "normal", GetColor(253, 253, 6), focusedMusicFontHandle);
	DrawStringToHandle(340, 120, normalNum.c_str(), fontColor, difficultyFontHandle,edgeColor);
	DrawStringToHandle(545, 170, "hard", GetColor(255, 11, 4), focusedMusicFontHandle);
	DrawStringToHandle(540, 120, hardNum.c_str(), fontColor, difficultyFontHandle,edgeColor);
}

void Game::Menu::Game_Menu_MenuManager::drawKeyConf() {
	DrawString(10, 720, "決定:enter", fontColor, edgeColor);
	DrawString(105, 720, "選択:↑↓", fontColor, edgeColor);
	DrawString(190, 720, "難易度:←→", fontColor, edgeColor);
	DrawString(290, 720, "タイトルへ:escape", fontColor, edgeColor);
}

void Game::Menu::Game_Menu_MenuManager::setDifficultyFocusedMusicDataStr() {
	//BPM
	bpm = "BPM :";
	bpm.append(std::to_string(static_cast<std::uint16_t>(p_focusedMusicData->at(0)->getBpm())));
	//難易度
	const std::ios::fmtflags curret_flag = std::cout.flags();
	std::ostringstream ss;
	ss << std::setw(2) << std::setfill('0') << p_focusedMusicData->at(0)->getLevel();
	easyNum = ss.str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << p_focusedMusicData->at(1)->getLevel();
	normalNum = ss.str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << p_focusedMusicData->at(2)->getLevel();
	hardNum = ss.str();
	std::cout.flags(curret_flag);
	for (int i = 0; i < difficultyCountBorder; ++i) {
		//ベストスコア
		bestScore[i] = "BestScore :";
		bestScore[i].append(std::to_string(p_focusedMusicData->at(i)->getBestScore()));
		// クリア状況
		if (p_focusedMusicData->at(i)->getIsClear()) {
			clearStatus[i] = "Clear";
			if (p_focusedMusicData->at(i)->getIsFullChain()) {
				clearStatus[i] = "FullChain";
				if (p_focusedMusicData->at(i)->getIsPerfect()) {
					clearStatus[i] = "PerfectFullChain";
				}
			}
		}
		else if (p_focusedMusicData->at(i)->getBestScore() == NULL) {
			clearStatus[i] = "Not Played";
		}
		else {
			clearStatus[i] = "Played";
		}
	}
}

void Game::Menu::Game_Menu_MenuManager::setNextFocusedMusicData() {
	musicDataVecElementDeq.push_back(musicDataVecElementDeq.front());
	musicDataVecElementDeq.pop_front();
	p_focusedMusicData = &musicDataVec.at(musicDataVecElementDeq.front());
	setDifficultyFocusedMusicDataStr();
}

void Game::Menu::Game_Menu_MenuManager::setPrevFocusedMusicData() {
	musicDataVecElementDeq.push_front(musicDataVecElementDeq.back());
	musicDataVecElementDeq.pop_back();
	p_focusedMusicData = &musicDataVec.at(musicDataVecElementDeq.front());
	setDifficultyFocusedMusicDataStr();
}