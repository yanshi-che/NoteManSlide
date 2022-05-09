#include "Make_Dialog_SaveFile.h"

bool Make::Dialog::Make_Dialog_SaveFile::isShowMusicInfoDlg = true;
bool  Make::Dialog::Make_Dialog_SaveFile::isInputed =false;

INT_PTR CALLBACK  Make::Dialog::Make_Dialog_SaveFile::saveFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
			const char* filter[] = { "mp3 wave ogg\0*.mp3;*.wave;*.ogg\0\0" };
			char filePath[MAX_PATH] = "";
			File::Make_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath, false);
			SetDlgItemText(hWnd, IDC_EDITMusicFilePath, filePath);
		}
		break;
		case IDOK:
		{
			bool isError = false;
			std::string errorMessage;
			char saveFilePath[MAX_PATH] = "";
			char musicFilePath[MAX_PATH] = "";
			GetDlgItemText(hWnd, IDC_EDITSaveFilePath, saveFilePath,MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDITMusicFilePath, musicFilePath,MAX_PATH);
			if (saveFilePath[0] == NULL) {
				errorMessage.append("�Z�[�u�t�@�C���p�X�������͂ł��B\n");
				isError = true;
			}
			if (musicFilePath[0] == NULL) {
				errorMessage.append("���y�t�@�C���p�X�������͂ł��B\n");
				isError = true;
			}
			if (isError) {
				MessageBox(hWnd, errorMessage.c_str(), "�G���[", MB_OK);
			}
			else {
				isShowMusicInfoDlg = false;
				isInputed = true;
				EndDialog(hWnd, NULL);
			}
		}
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
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_SaveFile), hMainWnd, saveFileDialogProc);

	//�e���ڂ̐����̐ݒ�
	SetDlgItemText(hDialogWnd, IDC_BUTTONSaveFilePath, "noteman�t�@�C���I��");
	SetDlgItemText(hDialogWnd, IDC_BUTTONMusicFilePath, "���y�t�@�C���I��");

	//�_�C�A���O��DX���C�u�����ɓo�^(DX���C�u�����͒P��̃_�C�A���O�̂ݑΉ�)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�_�C�A���O�{�b�N�X�̓��͂��I���܂ő҂�
		ScreenFlip();
	}

	if (isInputed) {
		GetDlgItemText(hDialogWnd, IDC_EDITSaveFilePath, saveFilePath, MAX_PATH);
		GetDlgItemText(hDialogWnd, IDC_EDITMusicFilePath, musicFilePath, MAX_PATH);
	}

	isShowMusicInfoDlg = true;
	isInputed = false;

	DestroyWindow(hDialogWnd);
}