#include "Make_Play_MusicPlayer.h"

Make::Play::Make_Play_MusicPlayer::Make_Play_MusicPlayer(const int musicHandle, const int channels, const int bitsPerSample, const int samplesParSec) :
musicHandle(musicHandle),channels(channels),bitsPerSample(bitsPerSample),samplesParSec(samplesParSec){

}

Make::Play::Make_Play_MusicPlayer::~Make_Play_MusicPlayer() {
	DeleteSoundMem(musicHandle);
}

void Make::Play::Make_Play_MusicPlayer::startMusicFromHead() {

	PlaySoundMem(musicHandle, DX_PLAYTYPE_BACK,true);
}

void Make::Play::Make_Play_MusicPlayer::startMusicFromMiddle() {
	PlaySoundMem(musicHandle, DX_PLAYTYPE_BACK,false);
}

void Make::Play::Make_Play_MusicPlayer::stopMusic() {
	StopSoundMem(musicHandle);
}

void Make::Play::Make_Play_MusicPlayer::setMusicSec(std::uint16_t second) {
	std::int64_t position = static_cast<std::int64_t>(samplesParSec) * second;
	bool isPlaying = false;
	if (CheckSoundMem(musicHandle) == 1) {
		stopMusic();
		isPlaying = true;
	}
	SetCurrentPositionSoundMem(position, musicHandle);
	if (isPlaying) {
		startMusicFromMiddle();
	}
}

void Make::Play::Make_Play_MusicPlayer::forwardOneSec() {
	bool isPlaying = false;
	if (CheckSoundMem(musicHandle) == 1) {
		stopMusic();
		isPlaying = true;
	}
	std::int64_t position = GetCurrentPositionSoundMem(musicHandle) + samplesParSec;
	SetCurrentPositionSoundMem(position, musicHandle);
	if (isPlaying) {
		startMusicFromMiddle();
	}
}

void Make::Play::Make_Play_MusicPlayer::backOneSec() {
	bool isPlaying = false;
	if (CheckSoundMem(musicHandle) == 1) {
		stopMusic();
		isPlaying = true;
	}
	std::int64_t position = GetCurrentPositionSoundMem(musicHandle) - samplesParSec;
	SetCurrentPositionSoundMem(position, musicHandle);
	if (isPlaying) {
		startMusicFromMiddle();
	}
}

bool Make::Play::Make_Play_MusicPlayer::isMiddle() {
	if (GetCurrentPositionSoundMem(musicHandle) != 0) {
		return true;
	}
	return false;
}