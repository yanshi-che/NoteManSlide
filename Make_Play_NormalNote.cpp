#include "Make_Play_NormalNote.h"

Make::Play::Make_Play_NormalNote::Make_Play_NormalNote(const double time, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight, const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote) :
time(time),noteType(noteType),laneIndex(laneIndex),laneXRight(laneXRight),laneXLeft(laneXLeft),nextNote(nextNote){

}