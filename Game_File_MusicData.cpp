#include "Game_File_MusicData.h"

Game::File::Game_File_MusicData::Game_File_MusicData(int mHandle, std::uint16_t bp, std::uint16_t bLength, double tMinutes,double bDlay,std::uint8_t numOfLane) :
musicHandle(mHandle),bpm(bp),barLength(bLength),totalMinutes(tMinutes),beginDelay(bDlay),amountOfLane(numOfLane){}

const std::uint16_t& Game::File::Game_File_MusicData::getBpm() noexcept{
	return bpm;
}

const std::uint16_t& Game::File::Game_File_MusicData::getBarLength() noexcept{
	return barLength;
}

const double& Game::File::Game_File_MusicData::getTotalMinutes() noexcept{
	return totalMinutes;
}

const double& Game::File::Game_File_MusicData::getBeginDelay() noexcept {
	return beginDelay;
}

const std::uint8_t& Game::File::Game_File_MusicData::getAmountOfLane() noexcept {
	return amountOfLane;
}

const int& Game::File::Game_File_MusicData::getMusicHandle() noexcept {
	return musicHandle;
}