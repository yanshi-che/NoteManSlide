#include "Make_Dialog_MusicInfo.h"

bool Make::Dialog::Make_Dialog_MusicInfo::isShowMusicInfoDlg = true;
bool Make::Dialog::Make_Dialog_MusicInfo::isInputed = false;

INT_PTR CALLBACK Make::Dialog::Make_Dialog_MusicInfo::MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDC_BUTTONFilePath:
		{
			const char* title[] = { "音楽ファイルの選択" };
			const char* filter[] = { "mp3 wave\0*.mp3;*.wave\0\0" };
			char filePath[MAX_PATH]= "";
			File::Make_File_BaseFile gfb;
			gfb.openExplorer(title, filter, filePath,false);
			SetDlgItemText(hWnd, IDC_EDITFilePath, filePath);
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

void Make::Dialog::Make_Dialog_MusicInfo::getMusicInfoFromDlg(char(&filePath)[MAX_PATH], char(&name)[MAX_PATH], char(&artist)[MAX_PATH], std::uint8_t& level, std::uint16_t& bpm, float& totalMinutes, std::uint16_t& beginDelay, std::uint8_t& amountOfLane) {
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
	SetDlgItemText(hDialogWnd, IDC_STATICNAME, "曲名(日本語入力できない場合はペーストしてください)");
	SetDlgItemText(hDialogWnd, IDC_STATICARTIST, "アーティスト名");
	SetDlgItemText(hDialogWnd, IDC_STATICLEVEL, "譜面の難易度(1～20)");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "再生時間(秒)");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "曲が始まるまでの時間(秒)");
	SetDlgItemText(hDialogWnd, IDC_STATICLANE, "レーン数(4～8)");

	//EDIITBOXの文字数制限
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITNAME), EM_SETLIMITTEXT, NAMECHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITARTIST), EM_SETLIMITTEXT, ARTISTCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITLEVEL), EM_SETLIMITTEXT, LEVELCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBPM), EM_SETLIMITTEXT, BPMCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITTotalMinutes), EM_SETLIMITTEXT, TOTALMINUTESCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBeginDelay), EM_SETLIMITTEXT, BEGINDELAYCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITLANE), EM_SETLIMITTEXT, amountOfLaneCHARMAX, NULL);

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
		GetDlgItemText(hDialogWnd, IDC_EDITFilePath, filePath, MAX_PATH);
		GetDlgItemText(hDialogWnd, IDC_EDITNAME, name, MAX_PATH);
		GetDlgItemText(hDialogWnd, IDC_EDITARTIST, artist, MAX_PATH);
		level = GetDlgItemInt(hDialogWnd, IDC_EDITLEVEL, NULL, true);
		bpm = GetDlgItemInt(hDialogWnd, IDC_EDITBPM, NULL, true);
		totalMinutes = GetDlgItemInt(hDialogWnd, IDC_EDITTotalMinutes, NULL, true) / Global::MINUTE;
		beginDelay = GetDlgItemInt(hDialogWnd, IDC_EDITBeginDelay, NULL, true);
		amountOfLane = GetDlgItemInt(hDialogWnd, IDC_EDITLANE, NULL, true);
		if (level < LEVELMIN) {
			level = LEVELMIN;
		}else if(LEVELMAX < level){
			level = LEVELMAX;
		}

		if(amountOfLane < LANEMIN){
			amountOfLane = LANEMIN;
		}
		else if(LANEMAX < amountOfLane){
			amountOfLane = LANEMAX;
		}
	}

	isShowMusicInfoDlg = true;
	isInputed = false;
}