#include "Make_Dialog_FailFile.h"

bool Make::Dialog::Make_Dialog_FailFile::isShowMusicInfoDlg = true;

INT_PTR CALLBACK  Make::Dialog::Make_Dialog_FailFile::failFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			isShowMusicInfoDlg = false;
			EndDialog(hWnd, NULL);
			break;
		case WM_CLOSE:
			isShowMusicInfoDlg = false;
			EndDialog(hWnd, NULL);
			break;
		}
		return 0;
	}
	return 0;
}

void Make::Dialog::Make_Dialog_FailFile::failFileDlg(const std::string& sentence) {
	HWND hMainWnd = nullptr;
	HWND hDialogWnd = nullptr;
	HINSTANCE hInstance = nullptr;
	//���C���E�B���h�E�n���h���̕ۑ�
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//�_�C�A���O�̍쐬
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_FAILFILE), hMainWnd, failFileDialogProc);

	//�e���ڂ̐����̐ݒ�
	SetDlgItemText(hDialogWnd, IDC_STATICERRORSENTENCE, sentence.c_str());

	//�_�C�A���O��DX���C�u�����ɓo�^(DX���C�u�����͒P��̃_�C�A���O�̂ݑΉ�)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�_�C�A���O�{�b�N�X�̓��͂��I���܂ő҂�
		ScreenFlip();
	}
	isShowMusicInfoDlg = true;
}