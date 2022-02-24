#include "Make_Play_LongNote.h"

Make::Play::Make_Play_LongNote::Make_Play_LongNote(const double startTime, const double endTime, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight, const double laneXLeft, const std::function<void(std::uint8_t, std::uint8_t)> nextNote):
startTime(startTime),endTime(endTime),noteType(noteType),laneIndex(laneIndex),laneXRight(laneXRight),laneXLeft(laneXLeft),nextNote(nextNote){
	y = 0;
	done = false;
	turn = false;
	noteColor = GetColor(255, 255, 255);
}