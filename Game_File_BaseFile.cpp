#include "Game_File_BaseFile.h"

void Game::File::Game_File_BaseFile::openExplorer(const char* title[], const char* filter[],char (&filePath)[MAX_PATH]) const{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(filePath, 0, sizeof(filePath));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetMainWindowHandle();

	// �t�@�C���g���q�̐���
	ofn.lpstrFilter = *filter;

	// lpstrFile �Ɏw�肷��z��Ƀt�@�C���̃t���p�X���������܂�
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	// lpstrTitle �ɕ\�������_�C�A���O�̐����������܂�
	ofn.lpstrTitle = *title;

	GetOpenFileName(&ofn);
}