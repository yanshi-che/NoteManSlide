#include "Make_Dialog_SaveFile.h"

bool Make::Dialog::Make_Dialog_SaveFile::isShowMusicInfoDlg = true;
bool  Make::Dialog::Make_Dialog_SaveFile::isInputed =false;

INT_PTR CALLBACK  Make::Dialog::Make_Dialog_SaveFile::saveFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
				errorMessage.append("セーブファイルパスが未入力です。\n");
				isError = true;
			}
			if (musicFilePath[0] == NULL) {
				errorMessage.append("音楽ファイルパスが未入力です。\n");
				isError = true;
			}
			if (isError) {
				MessageBox(hWnd, errorMessage.c_str(), "エラー", MB_OK);
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
	//メインウィンドウハンドルの保存
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//ダイアログの作成
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_SaveFile), hMainWnd, saveFileDialogProc);

	//各項目の説明の設定
	SetDlgItemText(hDialogWnd, IDC_BUTTONSaveFilePath, "notemanファイル選択");
	SetDlgItemText(hDialogWnd, IDC_BUTTONMusicFilePath, "音楽ファイル選択");

	//ダイアログをDXライブラリに登録(DXライブラリは単一のダイアログのみ対応)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ダイアログボックスの入力が終わるまで待つ
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