#include "Game_File_MusicAnalyse.h"

Game::File::Game_File_MusicAnalyse::Game_File_MusicAnalyse():COUNTOFBEAT(4){}

double Game::File::Game_File_MusicAnalyse::analyseBarLengthPerMinutes(std::uint8_t& bpm) const noexcept{
	return bpm / COUNTOFBEAT;
}

void Game::File::Game_File_MusicAnalyse::analyseBarLength(std::uint8_t& bpm,double& totalMinutes, std::uint16_t& barLength) const noexcept {
	barLength = std::ceil(totalMinutes / analyseBarLengthPerMinutes(bpm));
}

void Game::File::Game_File_MusicAnalyse::analyse(std::uint8_t& bpm, double& totalMinutes, double& beginDelay, std::uint16_t& barLength) {
	analyseBarLength(bpm,totalMinutes,barLength);
}