#include "Make_File_MusicAnalyse.h"

Make::File::Make_File_MusicAnalyse::Make_File_MusicAnalyse():COUNTOFBEAT(4){}

double Make::File::Make_File_MusicAnalyse::analyseBarLengthPerMinutes(double bpm) const noexcept{
	return static_cast<double>(bpm / COUNTOFBEAT);
}

void Make::File::Make_File_MusicAnalyse::analyseBarLength(double bpm,double totalMinutes, std::uint16_t& barLength) const noexcept {
	barLength = static_cast<std::uint16_t>(std::ceil(totalMinutes * analyseBarLengthPerMinutes(bpm)));
}

void Make::File::Make_File_MusicAnalyse::analyse(double bpm,double totalMinutes, std::uint16_t& barLength) {
	analyseBarLength(bpm,totalMinutes,barLength);
}