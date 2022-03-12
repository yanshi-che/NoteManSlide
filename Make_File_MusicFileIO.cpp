#include "Make_File_MusicFileIO.h"

std::pair < std::unique_ptr < Make::File::Make_File_MusicData > , std::unique_ptr<Make::Play::Make_Play_MusicPlayer>> Make::File::Make_File_MusicFileIO::getMusicFile() {
	char filePath[MAX_PATH]="";//���y�t�@�C���̃p�X
	char tempName[MAX_PATH] = "";//�Ȗ�
	char tempArtist[MAX_PATH] = "";//�A�[�e�B�X�g��

	std::uint16_t level = 1;//���ʂ̓�Փx
	double bpm = 0;//�Ȃ�bpm
	double totalMinutes = 0;//���y�t�@�C���̑��Đ�����
	double beginDelay = 0;//�����t�@�C�����Đ����Ă���Ȃ�����n�߂�܂ł̎���

	Dialog::Make_Dialog_MusicInfo gfm;
	gfm.getMusicInfoFromDlg(filePath,tempName,tempArtist,level,bpm,totalMinutes,beginDelay);

	if (filePath[0] == NULL) {
		return std::pair <std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>>(nullptr, nullptr);
	}

	std::string name(tempName);//�Ȗ�
	std::string artist(tempArtist);//�A�[�e�B�X�g��

	int musicHandle = 0;//���y�t�@�C���̃n���h��
	int softSoundHandle = 0;
	int channels, bitsPerSample, samplesParSec;
	try {
		musicHandle = LoadSoundMem(filePath);
		if (musicHandle == -1) {
			throw "���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		}
		softSoundHandle = LoadSoftSound(filePath);
		if (softSoundHandle == -1) {
			throw "�\�t�g�E�F�A�T�E���h�n���h���̓ǂݍ��݂Ɏ��s���܂���";
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

	std::uint16_t barLength;//�ȑS�̂̏��ߐ�
	Make_File_MusicAnalyse ma;
	ma.analyse(bpm,totalMinutes,barLength); //�y�Ȃ����

	return std::pair <std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>>(
		std::make_unique<Make_File_MusicData>(name,artist,level,bpm, barLength, totalMinutes, beginDelay),
		std::make_unique<Play::Make_Play_MusicPlayer>(musicHandle,channels,bitsPerSample,samplesParSec));
}
