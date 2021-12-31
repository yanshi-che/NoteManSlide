#include "Game_Draw_BeatLineDraw.h"

#include <iostream>

Game::Draw::Game_Draw_BeatLineDraw::Game_Draw_BeatLineDraw() {
	musicData = nullptr;
	quontize = 4;
}

void Game::Draw::Game_Draw_BeatLineDraw::setMusicData(File::Game_File_MusicData* data) noexcept{
	musicData = data;
	initialize();
}

void Game::Draw::Game_Draw_BeatLineDraw::setQuontize(std::uint8_t quon) noexcept{
	quontize = quon;
}

void Game::Draw::Game_Draw_BeatLineDraw::initialize() {
	std::uint8_t initialQuontize = 4;
	double timeSum = musicData->getBeginDelay();
	double timePerBeat = (musicData->getTotalMinutes() / musicData->getBarLength() / initialQuontize);
	std::int32_t initialY = 700;
	std::int32_t yWidth = 50;
	barVec.resize(musicData->getBarLength());
	for (int i = 0; i < musicData->getBarLength(); i++) {
		barVec.at(i).resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			barVec.at(i).at(k)=std::make_unique<Game_Draw_LineContainer>(i, musicData->getNumberOfRane(), timeSum, k, initialY);
			timeSum += timePerBeat;
			initialY -= yWidth;
		}
	}
}

void Game::Draw::Game_Draw_BeatLineDraw::draw() {
	if (musicData != nullptr) {
		for (int i = 0; i < barVec.size(); i++) {
			for (int k = 0; k < barVec.at(i).size(); k++) {
				barVec.at(i).at(k)->draw();
			}
		}
	}
}