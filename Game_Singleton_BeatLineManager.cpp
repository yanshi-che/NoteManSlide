#include "Game_Singleton_BeatLineManager.h"

#include <string>

Game::Singleton::Game_Singleton_BeatLineManager* Game::Singleton::Game_Singleton_BeatLineManager::instance = nullptr;

Game::Singleton::Game_Singleton_BeatLineManager* Game::Singleton::Game_Singleton_BeatLineManager::getInstance() {
	if (instance == nullptr) {
		instance = new Game_Singleton_BeatLineManager();
	}
	return instance;
}

void Game::Singleton::Game_Singleton_BeatLineManager::destroyInstance() {
	delete instance;
}

Game::Singleton::Game_Singleton_BeatLineManager::Game_Singleton_BeatLineManager(){
	musicData = nullptr;
	noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	y = 0;
	yMagnification = 25;
	initBarLineFunction = nullptr;
	quontize = Global::QUARTER;
}

void Game::Singleton::Game_Singleton_BeatLineManager::setMusicData(File::Game_File_MusicData* data){
	musicData = data;
	initialize(quontize,1.0);
}

void Game::Singleton::Game_Singleton_BeatLineManager::initialize(std::uint8_t initialQuontize, double separateBarWidth) {
	double timeSum = musicData->getBeginDelay();
	double timePerBeat = (musicData->getTotalMinutes() * Global::MINUTE / musicData->getBarLength() / initialQuontize);
	std::int32_t initY = initialY;
	std::uint8_t yWidth = static_cast<std::uint8_t>(yWidthRegular * separateBarWidth);
	std::int32_t yMax = 0;
	noteManager->initVector(&musicData->getBarLength(),initialQuontize);
	barVec.resize(musicData->getBarLength());
	for (int i = 0; i < musicData->getBarLength(); i++) {
		barVec[i].resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initY + (yWidth * musicData->getBarLength() * initialQuontize) - Game::Global::WINDOW_HEIGHT / 2;
			barVec[i][k]=std::make_unique<Draw::Game_Draw_LineContainer>(i, &musicData->getNumberOfRane(), timeSum, k, initY,yMax);
			timeSum += timePerBeat;
			initY -= yWidth;
		}
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::initAllBarLineByQuontize() {
	resetBarVec(true);
	noteManager->resetVector(true);
	double separate = 1.0;
	checkSeparate(separate);
	initialize(quontize,separate);
}

void Game::Singleton::Game_Singleton_BeatLineManager::initOneBarLineByQuontize() {
	std::uint16_t id = Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize();
	std::uint16_t beforeQuontize = barVec[id].size();
	//ロングノーツがまたがっていたら削除処理
	for (int i = 1,isize= barVec[id].size(); i < isize; ++i) {
		for (int k = 0, ksize = musicData->getNumberOfRane(); k < ksize; ++k) {
			noteManager->setLongNote(id, i, k,nullptr,true);
		}
	}
	//vectorの初期化とリサイズ
	resetBarVec(false);
	noteManager->resetVector(false);
	double separate = 1.0;
	checkSeparate(separate);
	noteManager->initOneVector(quontize);

	// 新たな拍線の作成
	double timePerBeat = (musicData->getTotalMinutes() * Global::MINUTE / musicData->getBarLength() / quontize);
	double timeSum = barVec[id][0]->getTime();
	std::int32_t yWidth = static_cast<std::uint8_t>(yWidthRegular * separate);
	std::int32_t initY = barVec[id][0]->getY();
	std::int32_t yMax = barVec[id][0]->getYMax();
	std::int32_t yMin = barVec[id][0]->getYMin();
	std::int32_t yChange = 0;//変更した小節全体の幅
	barVec[id].resize(quontize);
	for (int i = 1; i < quontize; ++i) {
		timeSum += timePerBeat;
		initY -= yWidth;
		yMax -= yWidth;
		yMin -= yWidth;
		yChange -= yWidth;
		barVec[id][i] = std::make_unique<Draw::Game_Draw_LineContainer>(id, &musicData->getNumberOfRane(), timeSum, i, initY, yMax);
		barVec[id][i]->setYMin(yMin);
	}

	//変更した小節より後の小節の座標調整
	yChange -= yWidth;
	if (id < musicData->getBarLength() - 1) {
		yChange = yChange + (barVec[id][0]->getY() - barVec[id + 1][0]->getY());//変化量
		for (int i = 0; i < id; ++i) {
			for (int k = 0, ksize = barVec[i].size(); k < ksize; ++k) {
				barVec[i][k]->updateYMax(yChange);
			}
		}
		for (int i = id + 1, isize = barVec.size(); i < isize; ++i) {
			for (int k = 0, ksize = barVec[i].size(); k < ksize; ++k) {
				barVec[i][k]->updateByInitOneBar(yChange);
			}
		}
	}
	else {
		if (beforeQuontize < quontize) {
			yChange = -yChange;
		}
		for (int i = 0; i <= id; ++i) {
			for (int k = 0, ksize = barVec[i].size(); k < ksize; ++k) {
				barVec[i][k]->updateYMax(yChange);
			}
		}
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::checkSeparate(double& separate) {
	switch (quontize) {
	case Global::EIGHTH:
		separate = 0.8;
		break;
	case Global::SIXTEENTH:
		separate = 0.6;
		break;
	case Global::THIRTYSECOND:
		separate = 0.4;
		break;
	case Global::TRIPLET:
		separate = 0.75;
		break;
	}
}

void Game::Singleton::Game_Singleton_BeatLineManager::resetBarVec(bool isAll) {
	if (isAll) {
		for (int i = 0, isize = barVec.size(); i < isize; ++i) {
			for (int k = 0, ksize = barVec[i].size(); k < ksize; ++k) {
				barVec[i][k].reset();
			}
		}
	}
	else {
		std::uint16_t id = Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize();
		for (int i = 1, isize = barVec[id].size(); i < isize; ++i) {
			barVec[id][i].reset();
		}
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