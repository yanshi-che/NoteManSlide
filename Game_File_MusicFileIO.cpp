#include "Game_File_MusicFileIO.h"

std::unique_ptr<Game::File::Game_File_MusicData> Game::File::Game_File_MusicFileIO::getMusicFile() {
	char filePath[MAX_PATH]="";//���y�t�@�C���̃p�X
	std::uint16_t bpm = 0;//�Ȃ�bpm
	double totalMinutes = 0;//���y�t�@�C���̑��Đ�����
	double beginDelay = 0;//�����t�@�C�����Đ����Ă���Ȃ�����n�߂�܂ł̎���
	std::uint8_t numberOfRane = 4;//���[����

	Dialog::Game_Dialog_MusicInfo gfm;
	gfm.getMusicInfoFromDlg(filePath,bpm,totalMinutes,beginDelay,numberOfRane);

	if (filePath==""||bpm==0||totalMinutes==0||beginDelay==0) {
		return nullptr;
	}

	int musicHandle = 0;//���y�t�@�C���̃n���h��
	try {
		musicHandle = LoadSoundMem(filePath);
		if (musicHandle == -1) {
			throw "���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		}
	}
	catch (const std::string e) {
		DrawString(50, 50, e.c_str(), GetColor(255, 255, 255));//���u��
		return nullptr;
	}

	std::uint16_t barLength;//�ȑS�̂̏��ߐ�
	Game_File_MusicAnalyse ma;
	ma.analyse(bpm,totalMinutes,beginDelay,barLength); //�y�Ȃ����

	return std::make_unique<Game_File_MusicData>(musicHandle, bpm, barLength, totalMinutes, beginDelay,numberOfRane);
}
