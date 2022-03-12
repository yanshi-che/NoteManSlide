#include "Make_File_MusicFileIO.h"

std::pair < std::unique_ptr < Make::File::Make_File_MusicData > , std::unique_ptr<Make::Play::Make_Play_MusicPlayer>> Make::File::Make_File_MusicFileIO::getMusicFile() {
	char filePath[MAX_PATH]="";//音楽ファイルのパス
	char tempName[MAX_PATH] = "";//曲名
	char tempArtist[MAX_PATH] = "";//アーティスト名

	std::uint16_t level = 1;//譜面の難易度
	double bpm = 0;//曲のbpm
	double totalMinutes = 0;//音楽ファイルの総再生時間
	double beginDelay = 0;//音声ファイルを再生してから曲が流れ始めるまでの時間

	Dialog::Make_Dialog_MusicInfo gfm;
	gfm.getMusicInfoFromDlg(filePath,tempName,tempArtist,level,bpm,totalMinutes,beginDelay);

	if (filePath[0] == NULL) {
		return std::pair <std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>>(nullptr, nullptr);
	}

	std::string name(tempName);//曲名
	std::string artist(tempArtist);//アーティスト名

	int musicHandle = 0;//音楽ファイルのハンドル
	int softSoundHandle = 0;
	int channels, bitsPerSample, samplesParSec;
	try {
		musicHandle = LoadSoundMem(filePath);
		if (musicHandle == -1) {
			throw "音楽ファイルの読み込みに失敗しました";
		}
		softSoundHandle = LoadSoftSound(filePath);
		if (softSoundHandle == -1) {
			throw "ソフトウェアサウンドハンドルの読み込みに失敗しました";
		}
		GetSoftSoundFormat(softSoundHandle, &channels, &bitsPerSample, &samplesParSec);
	}
	catch (const char* e) {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence(e);
		f.failFileDlg(errSentence);
		return std::pair <std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>>(nullptr,nullptr);
	}
	DeleteSoftSound(softSoundHandle);

	std::uint16_t barLength;//曲全体の小節数
	Make_File_MusicAnalyse ma;
	ma.analyse(bpm,totalMinutes,barLength); //楽曲を解析

	return std::pair <std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>>(
		std::make_unique<Make_File_MusicData>(name,artist,level,bpm, barLength, totalMinutes, beginDelay),
		std::make_unique<Play::Make_Play_MusicPlayer>(musicHandle,channels,bitsPerSample,samplesParSec));
}
