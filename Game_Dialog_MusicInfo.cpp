#include "Game_Dialog_MusicInfo.h"

INT_PTR CALLBACK Game::Dialog::MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDC_BUTTONFilePath:
			const char* title[] = { "test" };
			const char* filter[] = { "mp3 wave\0*.mp3;*.wave\0\0" };
			char filePath[MAX_PATH];
			File::Game_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath);
			SetDlgItemText(hWnd, IDC_EDITFilePath, filePath);
			break;
		}
		break;
	case WM_CLOSE:

	}
	return 0;
}

void Game::Dialog::Game_Dialog_MusicInfo::getMusicInfoFromDlg(char(&filePath)[MAX_PATH],std::uint8_t& bpm, double& totalMinutes, double& beginDlay) {
	HWND hMainWnd = nullptr;
	HWND hDialogWnd = nullptr;
	HINSTANCE hInstance = nullptr;
	//���C���E�B���h�E�n���h���̕ۑ�
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//�_�C�A���O�̍쐬
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MUSICINFO), hMainWnd, MusicInfoDialogProc);

	SetDlgItemText(hDialogWnd, IDC_BUTTONFilePath, "�t�@�C���I��");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "�Đ����ԁi3��35�b��335");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "�Ȃ������܂ł̃Y��");

	//�_�C�A���O��DX���C�u�����ɓo�^(DX���C�u�����͒P��̃_�C�A���O�̂ݑΉ�)
	SetDialogBoxHandle(hDialogWnd);

	while (isShowDlg) {
		Sleep(1000);
	}
	GetDlgItemText(hDialogWnd, IDC_EDDITFilePath,filePath,MAX_PATH);
}