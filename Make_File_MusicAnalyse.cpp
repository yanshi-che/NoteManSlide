#include "Make_File_MusicAnalyse.h"

Make::File::Make_File_MusicAnalyse::Make_File_MusicAnalyse():COUNTOFBEAT(4){}

float Make::File::Make_File_MusicAnalyse::analyseBarLengthPerMinutes(float bpm) const noexcept{
	return static_cast<float>(bpm / COUNTOFBEAT);
}

void Make::File::Make_File_MusicAnalyse::analyseBarLength(float bpm,float totalMinutes, std::uint16_t& barLength) const noexcept {
	barLength = static_cast<std::uint16_t>(std::ceil(totalMinutes * analyseBarLengthPerMinutes(bpm)));
}

void Make::File::Make_File_MusicAnalyse::analyse(float bpm,float totalMinutes, std::uint16_t& barLength) {
	analyseBarLength(bpm,totalMinutes,barLength);
}