#include "Make_File_MusicData.h"

Make::File::Make_File_MusicData::Make_File_MusicData(const int mHandle,const std::string& name,const std::string& artist,const std::uint8_t level,const std::uint16_t bp,const std::uint16_t bLength,const float tMinutes,const std::uint16_t bDlay,const std::uint8_t numOfLane) :
musicHandle(mHandle),name(name),artist(artist),level(level),bpm(bp),barLength(bLength),totalMinutes(tMinutes),beginDelay(bDlay),amountOfLane(numOfLane){}

const std::string& Make::File::Make_File_MusicData::getName() noexcept {
	return name;
}

const std::string& Make::File::Make_File_MusicData::getArtist() noexcept {
	return artist;
}

const std::uint8_t& Make::File::Make_File_MusicData::getLevel() noexcept {
	return level;
}

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