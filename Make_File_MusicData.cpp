#include "Make_File_MusicData.h"

Make::File::Make_File_MusicData::Make_File_MusicData(int mHandle,std::uint16_t bp,std::uint16_t bLength,float tMinutes,std::uint16_t bDlay,std::uint8_t numOfLane) :
musicHandle(mHandle),bpm(bp),barLength(bLength),totalMinutes(tMinutes),beginDelay(bDlay),amountOfLane(numOfLane){}

const std::uint16_t& Make::File::Make_File_MusicData::getBpm() noexcept{
	return bpm;
}

const std::uint16_t& Make::File::Make_File_MusicData::getBarLength() noexcept{
	return barLength;
}

const float& Make::File::Make_File_MusicData::getTotalMinutes() noexcept{
	return totalMinutes;
}

const std::uint16_t& Make::File::Make_File_MusicData::getBeginDelay() noexcept {
	return beginDelay;
}

const std::uint8_t& Make::File::Make_File_MusicData::getAmountOfLane() noexcept {
	return amountOfLane;
}

const int& Make::File::Make_File_MusicData::getMusicHandle() noexcept {
	return musicHandle;
}