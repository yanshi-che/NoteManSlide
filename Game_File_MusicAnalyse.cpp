#include "Game_File_MusicAnalyse.h"

Game::File::Game_File_MusicAnalyse::Game_File_MusicAnalyse():COUNTOFBEAT(4){}

float Game::File::Game_File_MusicAnalyse::analyseBarLengthPerMinutes(std::uint16_t bpm) const noexcept{
	return static_cast<float>(bpm / COUNTOFBEAT);
}

void Game::File::Game_File_MusicAnalyse::analyseBarLength(std::uint16_t bpm,float totalMinutes, std::uint16_t& barLength) const noexcept {
	barLength = static_cast<std::uint16_t>(std::ceil(totalMinutes * analyseBarLengthPerMinutes(bpm)));
}

void Game::File::Game_File_MusicAnalyse::analyse(std::uint16_t bpm,float totalMinutes, std::uint16_t& barLength) {
	analyseBarLength(bpm,totalMinutes,barLength);
}