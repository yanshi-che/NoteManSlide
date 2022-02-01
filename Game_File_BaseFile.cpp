#include "Game_File_BaseFile.h"

void Game::File::Game_File_BaseFile::openExplorer(const char* title[], const char* filter[],char (&filePath)[MAX_PATH],bool isSave) const{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(filePath, 0, sizeof(filePath));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetMainWindowHandle();

	// ファイル拡張子の制限
	ofn.lpstrFilter = *filter;

	// lpstrFile に指定する配列にファイルのフルパスが代入
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	// lpstrTitle に表示されるダイアログの説明を代入
	ofn.lpstrTitle = *title;

	if (!isSave) {
		GetOpenFileName(&ofn);
	}
	else {
		GetSaveFileName(&ofn);
	}
}