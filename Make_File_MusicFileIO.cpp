#include "Make_File_MusicFileIO.h"

std::unique_ptr<Make::File::Make_File_MusicData> Make::File::Make_File_MusicFileIO::getMusicFile() {
	char filePath[MAX_PATH]="";//音楽ファイルのパス
	std::uint16_t bpm = 0;//曲のbpm
	float totalMinutes = 0;//音楽ファイルの総再生時間
	std::uint16_t beginDelay = 0;//音声ファイルを再生してから曲が流れ始めるまでの時間
	std::uint8_t amountOfLane = 4;//レーン数

	Dialog::Make_Dialog_MusicInfo gfm;
	gfm.getMusicInfoFromDlg(filePath,bpm,totalMinutes,beginDelay,amountOfLane);

	if (filePath==""||bpm==0||totalMinutes==0) {
		return nullptr;
	}

	int musicHandle = 0;//音楽ファイルのハンドル
	try {
		musicHandle = LoadSoundMem(filePath);
		if (musicHandle == -1) {
			throw "音楽ファイルの読み込みに失敗しました";
		}
	}
	catch (const std::string e) {
		DrawString(50, 50, e.c_str(), GetColor(255, 255, 255));//仮置き
		return nullptr;
	}

	std::uint16_t barLength;//曲全体の小節数
	Make_File_MusicAnalyse ma;
	ma.analyse(bpm,totalMinutes,barLength); //楽曲を解析

	return std::make_unique<Make_File_MusicData>(musicHandle, bpm, barLength, totalMinutes, beginDelay,amountOfLane);
}
