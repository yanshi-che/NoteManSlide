#include "Game_File_MusicData.h"

Game::File::Game_File_MusicData::Game_File_MusicData(int mHandle, std::uint8_t bp, std::uint16_t bLength, double tMinutes,double bDlay) :
musicHandle(mHandle),bpm(bp),barLength(bLength),totalMinutes(tMinutes),beginDelay(bDlay){}
