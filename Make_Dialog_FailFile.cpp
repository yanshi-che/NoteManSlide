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
	//メインウィンドウハンドルの保存
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//ダイアログの作成
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_FAILFILE), hMainWnd, failFileDialogProc);

	//各項目の説明の設定
	SetDlgItemText(hDialogWnd, IDC_STATICERRORSENTENCE, sentence.c_str());

	//ダイアログをDXライブラリに登録(DXライブラリは単一のダイアログのみ対応)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ダイアログボックスの入力が終わるまで待つ
		ScreenFlip();
	}
	isShowMusicInfoDlg = true;
}