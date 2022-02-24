#include "Make_File_MusicData.h"

Make::File::Make_File_MusicData::Make_File_MusicData(const std::string& name,const std::string& artist,const std::uint8_t level,const double bp,const std::uint16_t bLength,const double tMinutes,const double bDlay) :
name(name),artist(artist),level(level),bpm(bp),barLength(bLength),totalMinutes(tMinutes),beginDelay(bDlay){}

const std::string& Make::File::Make_File_MusicData::getName() noexcept {
	return name;
}

const std::string& Make::File::Make_File_MusicData::getArtist() noexcept {
	return artist;
}

const std::uint8_t& Make::File::Make_File_MusicData::getLevel() noexcept {
	return level;
}

const double& Make::File::Make_File_MusicData::getBpm() noexcept{
	return bpm;
}

const std::uint16_t& Make::File::Make_File_MusicData::getBarLength() noexcept{
	return barLength;
}

const double& Make::File::Make_File_MusicData::getTotalMinutes() noexcept{
	return totalMinutes;
}

const double& Make::File::Make_File_MusicData::getBeginDelay() noexcept {
	return beginDelay;
}