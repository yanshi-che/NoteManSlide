#include "Make_Dialog_SaveFile.h"

bool Make::Dialog::Make_Dialog_SaveFile::isShowMusicInfoDlg = true;
bool  Make::Dialog::Make_Dialog_SaveFile::isInputed =false;

INT_PTR CALLBACK  Make::Dialog::Make_Dialog_SaveFile::SaveFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDC_BUTTONSaveFilePath:
		{
			const char* title[] = { "noteman�t�@�C���̑I��" };
			const char* filter[] = { "noteman\0*.noteman\0\0" };
			char filePath[MAX_PATH] = "";
			File::Make_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath, false);
			SetDlgItemText(hWnd, IDC_EDITSaveFilePath, filePath);
		}
		break;
		case IDC_BUTTONMusicFilePath:
		{
			const char* title[] = { "���y�t�@�C���̑I��" };
			const char* filter[] = { "mp3 wave\0*.mp3;*.wave\0\0" };
			char filePath[MAX_PATH] = "";
			File::Make_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath, false);
			SetDlgItemText(hWnd, IDC_EDITMusicFilePath, filePath);
		}
		break;
		case IDOK:
			isShowMusicInfoDlg = false;
			isInputed = true;
			EndDialog(hWnd, NULL);
			break;
		case IDCANCEL:
			isShowMusicInfoDlg = false;
			EndDialog(hWnd, NULL);
			break;
		}
		break;
	case WM_CLOSE:
		isShowMusicInfoDlg = false;
		EndDialog(hWnd, NULL);
	}
	return 0;
}

void Make::Dialog::Make_Dialog_SaveFile::getSaveFilePathFromDlg(char(&saveFilePath)[MAX_PATH], char(&musicFilePath)[MAX_PATH]) {
	HWND hMainWnd = nullptr;
	HWND hDialogWnd = nullptr;
	HINSTANCE hInstance = nullptr;
	//���C���E�B���h�E�n���h���̕ۑ�
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//�_�C�A���O�̍쐬
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_SaveFile), hMainWnd, SaveFileDialogProc);

	//�e���ڂ̐����̐ݒ�
	SetDlgItemText(hDialogWnd, IDC_BUTTONSaveFilePath, "noteman�t�@�C���I��");
	SetDlgItemText(hDialogWnd, IDC_BUTTONMusicFilePath, "���y�t�@�C���I��");

	//�_�C�A���O��DX���C�u�����ɓo�^(DX���C�u�����͒P��̃_�C�A���O�̂ݑΉ�)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg) {
		//�_�C�A���O�{�b�N�X�̓��͂��I���܂ő҂�
		ProcessMessage();
		ClearDrawScreen();
		ScreenFlip();
	}

	if (isInputed) {
		GetDlgItemText(hDialogWnd, IDC_EDITSaveFilePath, saveFilePath, MAX_PATH);
		GetDlgItemText(hDialogWnd, IDC_EDITMusicFilePath, musicFilePath, MAX_PATH);
	}

	isShowMusicInfoDlg = true;
	isInputed = false;
}