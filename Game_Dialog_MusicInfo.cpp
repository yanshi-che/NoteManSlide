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
		case IDOK:
			isShowMusicInfoDlg = false;
			isInputed = true;
			EndDialog(hWnd,NULL);
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

Game::Dialog::Game_Dialog_MusicInfo::Game_Dialog_MusicInfo() : MINUTE(60.0),BPMCHARMAX(3),TOTALMINUTESCHARMAX(4),BEGINDELAYCHARMAX(2){

}

void Game::Dialog::Game_Dialog_MusicInfo::getMusicInfoFromDlg(char(&filePath)[MAX_PATH], std::uint8_t& bpm, double& totalMinutes, double& beginDelay) {
	HWND hMainWnd = nullptr;
	HWND hDialogWnd = nullptr;
	HINSTANCE hInstance = nullptr;
	//メインウィンドウハンドルの保存
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//ダイアログの作成
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MUSICINFO), hMainWnd, MusicInfoDialogProc);

	//各項目の説明の設定
	SetDlgItemText(hDialogWnd, IDC_BUTTONFilePath, "ファイル選択");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "再生時間（秒)");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "曲が流れ始めるまでの時間(秒)");

	//EDIITBOXの文字数制限
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBPM), EM_SETLIMITTEXT, BPMCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITTotalMinutes), EM_SETLIMITTEXT, TOTALMINUTESCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBeginDelay), EM_SETLIMITTEXT, BEGINDELAYCHARMAX, NULL);

	//ダイアログをDXライブラリに登録(DXライブラリは単一のダイアログのみ対応)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg) {
		//ダイアログボックスの入力が終わるまで待つ
		ProcessMessage();
		ClearDrawScreen();
		ScreenFlip();
	}

	if (isInputed) {
		GetDlgItemText(hDialogWnd, IDC_EDDITFilePath, filePath, MAX_PATH);
		bpm = GetDlgItemText(hDialogWnd, IDC_EDITBPM, NULL, true);
		totalMinutes = GetDlgItemText(hDialogWnd, IDC_EDITTotalMinutes, NULL, true) / MINUTE;
		beginDelay = GetDlgItemText(hDialogWnd, IDC_EDITBeginDelay, NULL, true);
	}
}