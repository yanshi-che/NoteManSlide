#include "Game_Singleton_BeatLineDraw.h"

#include <string>

Game::Singleton::Game_Singleton_BeatLineDraw* Game::Singleton::Game_Singleton_BeatLineDraw::instance = nullptr;

Game::Singleton::Game_Singleton_BeatLineDraw* Game::Singleton::Game_Singleton_BeatLineDraw::getInstance() {
	if (instance == nullptr) {
		instance = new Game_Singleton_BeatLineDraw();
	}
	return instance;
}

void Game::Singleton::Game_Singleton_BeatLineDraw::destroyInstance() {
	delete instance;
}

Game::Singleton::Game_Singleton_BeatLineDraw::Game_Singleton_BeatLineDraw(){
	musicData = nullptr;
	noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	y = 0;
	yMagnification = 25;
}

void Game::Singleton::Game_Singleton_BeatLineDraw::setMusicData(File::Game_File_MusicData* data){
	musicData = data;
	initialize(4,1.0);
}

void Game::Singleton::Game_Singleton_BeatLineDraw::initialize(std::uint8_t initialQuontize, double separateBarWidth) {
	double timeSum = musicData->getBeginDelay();
	double timePerBeat = (musicData->getTotalMinutes() * Global::MINUTE / musicData->getBarLength() / initialQuontize);
	std::int32_t initY = initialY;
	std::uint16_t yWidth = static_cast<std::uint16_t>(yWidthRegular * separateBarWidth);
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

void Game::Singleton::Game_Singleton_BeatLineDraw::initAllBarLineByQuontize(std::uint8_t quontize) {
//TODO draw()のfor文処理中にその時点でのクオンタイズよりも小さくするとクラッシュ
	resetBarVec();
	double separate = 1.0;
	switch(quontize) {
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
	initialize(quontize,separate);
}

void Game::Singleton::Game_Singleton_BeatLineDraw::initOneBarLineByQuontize(std::uint8_t quontize) {

}

void Game::Singleton::Game_Singleton_BeatLineDraw::resetBarVec() {
	for (int i = 0, isize = barVec.size(); i < isize; ++i) {
		for (int k = 0, ksize = barVec[i].size(); k < ksize; ++k) {
			barVec[i][k].reset();
		}
	}
}