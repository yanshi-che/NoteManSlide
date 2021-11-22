#include "Game_File_MusicFileIO.h"

void Game::File::Game_File_MusicFileIO::inputMusicInfo(std::uint8_t& bpm, double& totalMinutes,double& beginDelay) {

}

std::unique_ptr<Game::File::Game_File_MusicData> Game::File::Game_File_MusicFileIO::openMusicFile() {
	const char* title[] = { "�y�ȃf�[�^�̑I��" };
	const char* filter[] = { ".wave .mp3\0*.wave;*.mp3\0\0" };
	char filePath[MAX_PATH];
	openExplorer(title,filter,filePath); //�t�@�C���p�X�̓���

	std::uint8_t bpm = 0;
	double totalMinutes = 0;
	double beginDelay = 0;
	inputMusicInfo(bpm,totalMinutes,beginDelay);//bpm�Ɗy�Ȃ̍Đ����ԂƎn�܂钷���̓���

	int musicHandle = 0;
	std::uint16_t barLength;
	Game_File_MusicAnalyse ma;
	ma.analyse(filePath,bpm,totalMinutes,beginDelay,musicHandle,barLength); //�y�Ȃ���͂��Ċy�ȃf�[�^�̍쐬

	return std::make_unique<Game_File_MusicData>(musicHandle,bpm,barLength,totalMinutes,beginDelay);
}
