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
	//メインウィンドウハンドルの保存
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//ダイアログの作成
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MUSICINFO), hMainWnd, MusicInfoDialogProc);

	SetDlgItemText(hDialogWnd, IDC_BUTTONFilePath, "ファイル選択");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "再生時間（3分35秒→335");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "曲が流れるまでのズレ");

	//ダイアログをDXライブラリに登録(DXライブラリは単一のダイアログのみ対応)
	SetDialogBoxHandle(hDialogWnd);

	while (isShowDlg) {
		Sleep(1000);
	}
	GetDlgItemText(hDialogWnd, IDC_EDDITFilePath,filePath,MAX_PATH);
}