#include "Make_Singleton_BeatLineManager.h"

#include <string>

Make::Singleton::Make_Singleton_BeatLineManager* Make::Singleton::Make_Singleton_BeatLineManager::p_instance = nullptr;

Make::Singleton::Make_Singleton_BeatLineManager* Make::Singleton::Make_Singleton_BeatLineManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_BeatLineManager();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_BeatLineManager::destroyInstance() {
	delete p_instance;
}

Make::Singleton::Make_Singleton_BeatLineManager::Make_Singleton_BeatLineManager(){
	p_musicData = nullptr;
	scrBar = nullptr;
	p_noteManager = Singleton::Make_Singleton_NoteManager::getInstance();
	y = 0;
	totalScoreWidth = 0;
	yMagnificationByMouseWheel = 25.0f;
	initBarLineFunction = nullptr;
	quontize = Global::QUARTER;
}

void Make::Singleton::Make_Singleton_BeatLineManager::setMusicData(const std::shared_ptr<File::Make_File_MusicData>& data){
	p_musicData = data;
	initialize(quontize, 1.0f);
}

void Make::Singleton::Make_Singleton_BeatLineManager::initialize(std::uint8_t initialQuontize,float separateBarWidth) {
	float timeSum = p_musicData->getBeginDelay();
	const float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / initialQuontize);
	float initY = initialY;
	const float yWidth = yWidthRegular * separateBarWidth;
	float yMax = 0;
	totalScoreWidth = 0;
	p_noteManager->initVector(p_musicData->getBarLength(),initialQuontize);
	barVec.resize(p_musicData->getBarLength());
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	for (int i = 0,iSize = p_musicData->getBarLength(); i < iSize; i++) {
		barVec.at(i).resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initY + (yWidth * p_musicData->getBarLength() * initialQuontize) - Make::Global::WINDOW_HEIGHT *0.5f;
			barVec.at(i).at(k)=std::make_unique<Draw::Make_Draw_LineContainer>(i, amountOfLane, timeSum, k, initY,yMax);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}
	totalScoreWidth += Make::Global::WINDOW_HEIGHT * 0.5f;
	initScrollBar();
}

void Make::Singleton::Make_Singleton_BeatLineManager::initScrollBar() {
	scrBar = std::make_unique<Draw::Make_Draw_ScrollBar>(totalScoreWidth,barVec,yMagnificationByMouseWheel);
}

void Make::Singleton::Make_Singleton_BeatLineManager::draw() {
	if (p_musicData != nullptr) {
		y = GetMouseWheelRotVolF() * yMagnificationByMouseWheel;
		if (y != 0) {
			scrBar->updateBarY(y);
		}
		scrBar->draw();
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				if (y != 0) {
					barVec.at(i).at(k)->updateY(y);
				}
				barVec.at(i).at(k)->draw();
			}
		}
		if (initBarLineFunction != nullptr) {
			initBarLineFunction();
			initBarLineFunction = nullptr;
		}
	}
}

void Make::Singleton::Make_Singleton_BeatLineManager::initAllBarLineByQuontize() {
	resetScrollBar();
	resetBarVec(true);
	p_noteManager->resetVector(true);
	float separate = 1.0f;
	checkSeparate(separate);
	initialize(quontize,separate);
}

void Make::Singleton::Make_Singleton_BeatLineManager::initOneBarLineByQuontize() {
	std::uint16_t id = Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize();
	std::uint16_t beforeQuontize = static_cast<std::uint16_t>(barVec.at(id).size());
	//ロングノーツがまたがっていたら削除処理
	for (int i = 1,iSize= static_cast<int>(barVec.at(id).size()); i < iSize; ++i) {
		for (int k = 0, kSize = p_musicData->getAmountOfLane(); k < kSize; ++k) {
			p_noteManager->removeLongNote(id, i, k);
		}
	}
	//vectorの初期化とリサイズ、スクロールバーのリセット
	resetScrollBar();
	resetBarVec(false);
	p_noteManager->resetVector(false);
	float separate = 1.0f;
	checkSeparate(separate);

	//ノーツの初期化
	p_noteManager->initOneVector(quontize);

	// 新たな拍線の作成
	const float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / quontize);
	float timeSum = barVec.at(id).at(0)->getTime();
	const float yWidth = yWidthRegular * separate;
	float initY = barVec.at(id).at(0)->getY();
	float yMax = barVec.at(id).at(0)->getYMax();
	float yMin = barVec.at(id).at(0)->getYMin();
	float yChange = 0;//変更した小節全体の幅
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	barVec.at(id).resize(quontize);
	for (int i = 1; i < quontize; ++i) {
		timeSum += timePerBeat;
		initY -= yWidth;
		yMax -= yWidth;
		yMin -= yWidth;
		yChange -= yWidth;
		barVec.at(id).at(i) = std::make_unique<Draw::Make_Draw_LineContainer>(id, amountOfLane, timeSum, i, initY, yMax);
		barVec.at(id).at(i)->setYMin(yMin);
	}

	//変更した小節より後の小節の座標調整
	yChange -= yWidth;
	if (id < p_musicData->getBarLength() - 1) {
		yChange = yChange + (barVec.at(id).at(0)->getY() - barVec.at(id + 1).at(0)->getY());//変化量
		for (int i = 0; i < id; ++i) {
			for (int k = 0,kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k)->updateYMax(yChange);
			}
		}
		for (int i = id + 1,iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k)->updateByInitOneBar(yChange);
			}
		}
	}

	//スクロールバーの初期化
	totalScoreWidth -= yChange;
	initScrollBar();
	scrBar->updateBarY(barVec.at(0).at(0)->getY() - initialY);
}

void Make::Singleton::Make_Singleton_BeatLineManager::checkSeparate(float& separate) {
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

void Make::Singleton::Make_Singleton_BeatLineManager::resetBarVec(bool isAll) {
	if (isAll) {
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k).reset();
			}
		}
	}
	else {
		const std::uint16_t id = Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize();
		for (int i = 1, iSize = static_cast<int>(barVec.at(id).size()); i < iSize; ++i) {
			barVec.at(id).at(i).reset();
		}
	}
}

void Make::Singleton::Make_Singleton_BeatLineManager::resetScrollBar() {
	scrBar.reset();
}

void Make::Singleton::Make_Singleton_BeatLineManager::setInitBarLineFunc(std::uint8_t quon, bool isAll) {
	this->quontize = quon;
	if (isAll) {
		initBarLineFunction = [&]{return initAllBarLineByQuontize(); };
	}
	else {
		initBarLineFunction = [&]{return initOneBarLineByQuontize(); };
	}
}