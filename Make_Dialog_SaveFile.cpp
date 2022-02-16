#include "Make_Dialog_SaveFile.h"

bool Make::Dialog::Make_Dialog_SaveFile::isShowMusicInfoDlg = true;
bool  Make::Dialog::Make_Dialog_SaveFile::isInputed =false;

INT_PTR CALLBACK  Make::Dialog::Make_Dialog_SaveFile::SaveFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDC_BUTTONSaveFilePath:
		{
			const char* title[] = { "notemanファイルの選択" };
			const char* filter[] = { "noteman\0*.noteman\0\0" };
			char filePath[MAX_PATH] = "";
			File::Make_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath, false);
			SetDlgItemText(hWnd, IDC_EDITSaveFilePath, filePath);
		}
		break;
		case IDC_BUTTONMusicFilePath:
		{
			const char* title[] = { "音楽ファイルの選択" };
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
	//メインウィンドウハンドルの保存
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//ダイアログの作成
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_SaveFile), hMainWnd, SaveFileDialogProc);

	//各項目の説明の設定
	SetDlgItemText(hDialogWnd, IDC_BUTTONSaveFilePath, "notemanファイル選択");
	SetDlgItemText(hDialogWnd, IDC_BUTTONMusicFilePath, "音楽ファイル選択");

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
		GetDlgItemText(hDialogWnd, IDC_EDITSaveFilePath, saveFilePath, MAX_PATH);
		GetDlgItemText(hDialogWnd, IDC_EDITMusicFilePath, musicFilePath, MAX_PATH);
	}

	isShowMusicInfoDlg = true;
	isInputed = false;
}