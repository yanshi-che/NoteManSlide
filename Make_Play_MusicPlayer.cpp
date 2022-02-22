#include "Make_Play_MusicPlayer.h"

Make::Play::Make_Play_MusicPlayer::Make_Play_MusicPlayer(const int musicHandle, const int channels, const int bitsPerSample, const int samplesParSec) :
musicHandle(musicHandle),channels(channels),bitsPerSample(bitsPerSample),samplesParSec(samplesParSec){

}

Make::Play::Make_Play_MusicPlayer::~Make_Play_MusicPlayer() {
	DeleteSoundMem(musicHandle);
}