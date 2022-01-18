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

Game::Singleton::Game_Singleton_BeatLineDraw::Game_Singleton_BeatLineDraw() {
	musicData = nullptr;
	noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	y = 0;
	yMagnification = 25;
}

void Game::Singleton::Game_Singleton_BeatLineDraw::setMusicData(File::Game_File_MusicData* data) noexcept{
	musicData = data;
	initialize();
}

void Game::Singleton::Game_Singleton_BeatLineDraw::initialize() {
	std::uint8_t initialQuontize = 4;
	double timeSum = musicData->getBeginDelay();
	double timePerBeat = (musicData->getTotalMinutes() * Global::MINUTE / musicData->getBarLength() / initialQuontize);
	std::int32_t initialY = 700;
	std::int32_t yWidth = 50;
	std::int32_t yMax = 0;
	noteManager->resizeVector(&musicData->getBarLength(),initialQuontize);
	barVec.resize(musicData->getBarLength());
	for (int i = 0; i < musicData->getBarLength(); i++) {
		barVec[i].resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initialY + (yWidth * musicData->getBarLength() * initialQuontize) - Game::Global::WINDOW_HEIGHT / 2;
			barVec[i][k]=std::make_unique<Draw::Game_Draw_LineContainer>(i, &musicData->getNumberOfRane(), timeSum, k, initialY,yMax);
			timeSum += timePerBeat;
			initialY -= yWidth;
		}
	}
}