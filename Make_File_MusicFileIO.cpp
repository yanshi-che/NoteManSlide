#include "Make_File_MusicFileIO.h"

std::unique_ptr<Make::File::Make_File_MusicData> Make::File::Make_File_MusicFileIO::getMusicFile() {
	char filePath[MAX_PATH]="";//���y�t�@�C���̃p�X
	char tempName[MAX_PATH] = "";//�Ȗ�
	char tempArtist[MAX_PATH] = "";//�A�[�e�B�X�g��

	std::uint8_t level = 1;//���ʂ̓�Փx
	std::uint16_t bpm = 0;//�Ȃ�bpm
	float totalMinutes = 0;//���y�t�@�C���̑��Đ�����
	std::uint16_t beginDelay = 0;//�����t�@�C�����Đ����Ă���Ȃ�����n�߂�܂ł̎���
	std::uint8_t amountOfLane = 4;//���[����

	Dialog::Make_Dialog_MusicInfo gfm;
	gfm.getMusicInfoFromDlg(filePath,tempName,tempArtist,level,bpm,totalMinutes,beginDelay,amountOfLane);

	if (filePath==""||bpm==0||totalMinutes==0) {
		return nullptr;
	}

	std::string name(tempName);//�Ȗ�
	std::string artist(tempArtist);//�A�[�e�B�X�g��

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
	Make_File_MusicAnalyse ma;
	ma.analyse(bpm,totalMinutes,barLength); //�y�Ȃ����

	return std::make_unique<Make_File_MusicData>(musicHandle,name,artist,level,bpm, barLength, totalMinutes, beginDelay,amountOfLane);
}
