#include "Game_File_MusicFileIO.h"

void Game::File::Game_File_MusicFileIO::inputMusicInfo(std::uint8_t& bpm, double& totalMinutes,double& beginDelay) {

}

std::unique_ptr<Game::File::Game_File_MusicData> Game::File::Game_File_MusicFileIO::openMusicFile() {
	const char* title[] = { "楽曲データの選択" };
	const char* filter[] = { ".wave .mp3\0*.wave;*.mp3\0\0" };
	char filePath[MAX_PATH];
	openExplorer(title,filter,filePath); //ファイルパスの入手

	std::uint8_t bpm = 0;
	double totalMinutes = 0;
	double beginDelay = 0;
	inputMusicInfo(bpm,totalMinutes,beginDelay);//bpmと楽曲の再生時間と始まる長さの入手

	int musicHandle = 0;
	std::uint16_t barLength;
	Game_File_MusicAnalyse ma;
	ma.analyse(filePath,bpm,totalMinutes,beginDelay,musicHandle,barLength); //楽曲を解析して楽曲データの作成

	return std::make_unique<Game_File_MusicData>(musicHandle,bpm,barLength,totalMinutes,beginDelay);
}
