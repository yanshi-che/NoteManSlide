#include "Game_Play_SoundEffect.h"

Game::Play::Game_Play_SoundEffect::Game_Play_SoundEffect() {
	soundEffectHandle = 0;
	try {
		soundEffectHandle = LoadSoundMem(".\\data\\soundEffect\\se.ogg");
		ChangeVolumeSoundMem(200, soundEffectHandle);
	}
	catch (...) {
		soundEffectHandle = 0;
	}
}

Game::Play::Game_Play_SoundEffect::~Game_Play_SoundEffect() {
	DeleteSoundMem(soundEffectHandle);
}

void Game::Play::Game_Play_SoundEffect::playSoundEffect() {
	PlaySoundMem(soundEffectHandle, DX_PLAYTYPE_BACK, true);
}