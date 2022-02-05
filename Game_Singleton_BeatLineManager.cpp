#include "Game_Singleton_BeatLineManager.h"

#include <string>

Game::Singleton::Game_Singleton_BeatLineManager* Game::Singleton::Game_Singleton_BeatLineManager::p_instance = nullptr;

Game::Singleton::Game_Singleton_BeatLineManager* Game::Singleton::Game_Singleton_BeatLineManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Game_Singleton_BeatLineManager();
	}
	return p_instance;
}

void Game::Singleton::Game_Singleton_BeatLineManager::destroyInstance() {
	delete p_instance;
}

Game::Singleton::Game_Singleton_BeatLineManager::Game_Singleton_BeatLineManager(){
	p_musicData = nullptr;
	scrBar = nullptr;
	p_noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	y = 0;
	yMagnificationByMouseWheel = 25.0f;
	initBarLineFunction = nullptr;
	quontize = Global::QUARTER;
}

void Game::Singleton::Game_Singleton_BeatLineManager::setMusicData(const std::shared_ptr<File::Game_File_MusicData>& data){
	p_musicData = data;
	initialize(quontize, 1.0f);
}

void Game::Singleton::Game_Singleton_BeatLineManager::initialize(std::uint8_t initialQuontize,float separateBarWidth) {
	float timeSum = p_musicData->getBeginDelay();
	float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / initialQuontize);
	float initY = initialY;
	float yWidth = yWidthRegular * separateBarWidth;
	float yMax = 0;
	float totalScoreWidth = 0;
	p_noteManager->initVector(p_musicData->getBarLength(),initialQuontize);
	barVec.resize(p_musicData->getBarLength());
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	for (int i = 0,iSize = p_musicData->getBarLength(); i < iSize; i++) {
		barVec[i].resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initY + (yWidth * p_musicData->getBarLength() * initialQuontize) - Game::Global::WINDOW_HEIGHT *0.5f;
			barVec[i][k]=std::make_unique<Draw::Game_Draw_LineContainer>(i, amountOfLane, timeSum, k, initY,yMax);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}
	totalScoreWidth += Game::Global::WINDOW_HEIGHT * 0.5f;
	initScrollBar(totalScoreWidth);
}

void Game::Singleton::Game_Singleton_BeatLineManager::initScrollBar(float scoreWidth) {
	scrBar = std::make_unique<Draw::Game_Draw_ScrollBar>(scoreWidth,barVec,yMagnificationByMouseWheel);
}

void Game::Singleton::Game_Singleton_BeatLineManager::draw() {
	if (p_musicData != nullptr) {
		y = GetMouseWheelRotVolF() * yMagnificationByMouseWheel;
		scrBar->updateBarY(y);
		scrBar->draw();
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec[i].size()); k < kSize; ++k) {
				barVec[i][k]->updateY(y);
				barVec[i][k]->draw();
			}
		}
		if (initBarLineFunction != nullptr) {
			initBarLineFunction();
			initBarLineFunction = nullptr;
		}
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::initAllBarLineByQuontize() {
	resetBarVec(true);
	p_noteManager->resetVector(true);
	float separate = 1.0f;
	checkSeparate(separate);
	initialize(quontize,separate);
}

void Game::Singleton::Game_Singleton_BeatLineManager::initOneBarLineByQuontize() {
	std::uint16_t id = Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize();
	std::uint16_t beforeQuontize = static_cast<std::uint16_t>(barVec[id].size());
	//ロングノーツがまたがっていたら削除処理
	for (int i = 1,iSize= static_cast<int>(barVec[id].size()); i < iSize; ++i) {
		for (int k = 0, kSize = p_musicData->getAmountOfLane(); k < kSize; ++k) {
			p_noteManager->removeLongNote(id, i, k);
		}
	}
	//vectorの初期化とリサイズ
	resetBarVec(false);
	p_noteManager->resetVector(false);
	float separate = 1.0f;
	checkSeparate(separate);
	p_noteManager->initOneVector(quontize);

	// 新たな拍線の作成
	float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / quontize);
	float timeSum = barVec[id][0]->getTime();
	float yWidth = yWidthRegular * separate;
	float initY = barVec[id][0]->getY();
	float yMax = barVec[id][0]->getYMax();
	float yMin = barVec[id][0]->getYMin();
	float yChange = 0;//変更した小節全体の幅
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	barVec[id].resize(quontize);
	for (int i = 1; i < quontize; ++i) {
		timeSum += timePerBeat;
		initY -= yWidth;
		yMax -= yWidth;
		yMin -= yWidth;
		yChange -= yWidth;
		barVec[id][i] = std::make_unique<Draw::Game_Draw_LineContainer>(id, amountOfLane, timeSum, i, initY, yMax);
		barVec[id][i]->setYMin(yMin);
	}

	//変更した小節より後の小節の座標調整
	yChange -= yWidth;
	if (id < p_musicData->getBarLength() - 1) {
		yChange = yChange + (barVec[id][0]->getY() - barVec[id + 1][0]->getY());//変化量
		for (int i = 0; i < id; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec[i].size()); k < kSize; ++k) {
				barVec[i][k]->updateYMax(yChange);
			}
		}
		for (int i = id + 1, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec[i].size()); k < kSize; ++k) {
				barVec[i][k]->updateByInitOneBar(yChange);
			}
		}
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::checkSeparate(float& separate) {
	switch (quontize) {
	case Global::EIGHTH:
		separate = 0.5f;
		break;
	case Global::SIXTEENTH:
		separate = 0.25f;
		break;
	case Global::THIRTYSECOND:
		separate = 0.125f;
		break;
	case Global::TRIPLET:
		separate = 0.3333f;
		break;
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::resetBarVec(bool isAll) {
	if (isAll) {
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec[i].size()); k < kSize; ++k) {
				barVec[i][k].reset();
			}
		}
	}
	else {
		std::uint16_t id = Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize();
		for (int i = 1, iSize = static_cast<int>(barVec[id].size()); i < iSize; ++i) {
			barVec[id][i].reset();
		}
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::resetScrollBar(bool isAll) {
	if (isAll) {

	}
	else {

	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::setInitBarLineFunc(std::uint8_t quon, bool isAll) {
	this->quontize = quon;
	if (isAll) {
		initBarLineFunction = [&]{return initAllBarLineByQuontize(); };
	}
	else {
		initBarLineFunction = [&]{return initOneBarLineByQuontize(); };
	}
}