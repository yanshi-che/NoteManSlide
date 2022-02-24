#include "Make_Play_SlideNote.h"

Make::Play::Make_Play_SlideNote::Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXRight, const double laneXLeft, const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft, const std::uint8_t slideLaneIndexStart, const std::uint8_t slideLaneIndexEnd, const std::function<void(std::uint8_t, std::uint8_t)> nextNote) :
time(time),noteType(noteType),laneXRight(laneXRight),laneXLeft(laneXLeft),rightOrLeft(rightOrLeft),directionRightOrLeft(directionRightOrLeft),slideLaneIndexStart(slideLaneIndexStart),slideLaneIndexEnd(slideLaneIndexEnd),nextNote(nextNote){

}