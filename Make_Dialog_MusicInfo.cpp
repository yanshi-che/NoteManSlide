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
		{
			bool isError = false;
			std::string errorMessage;
			char filePath[MAX_PATH] = "";
			char name[NAMECHARMAX] = "";
			char artist[ARTISTCHARMAX] = "";
			char bpm[BPMCHARMAX] = "";
			char beginDelayText[BEGINDELAYCHARMAX] = "";
			GetDlgItemText(hWnd, IDC_EDITFilePath, filePath, MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDITNAME, name, NAMECHARMAX);
			GetDlgItemText(hWnd, IDC_EDITARTIST, artist, ARTISTCHARMAX);
			GetDlgItemText(hWnd, IDC_EDITBPM, bpm, BPMCHARMAX);
			GetDlgItemText(hWnd, IDC_EDITBeginDelay, beginDelayText, BEGINDELAYCHARMAX);
			std::regex isFloatForBpm(R"(^\d{1,3}\.\d{1,2})");
			std::regex isFloatForBeginDelay(R"(^\d{1,2}\.\d{1,2})");
			if (filePath[0] == NULL) {
				errorMessage.append("ファイルパスが未入力です。\n");
				isError = true;
			}
			if (name[0] == NULL) {
				errorMessage.append("曲名が未入力です。\n");
				isError = true;
			}
			if (artist[0] == NULL) {
				errorMessage.append("アーティストが未入力です。\n");
				isError = true;
			}
			if (GetDlgItemInt(hWnd, IDC_EDITLEVEL, NULL, true) < LEVELMIN || LEVELMAX < GetDlgItemInt(hWnd, IDC_EDITLEVEL, NULL, true)) {
				errorMessage.append("レベルが範囲外です。\n");
				isError = true;
			}
			if (!std::regex_match(bpm, isFloatForBpm)) {
				errorMessage.append("BPMがフォーマットと異なります\n");
				isError = true;
			}
			if (GetDlgItemInt(hWnd, IDC_EDITTotalMinutes, NULL, true) == NULL) {
				errorMessage.append("再生時間が未入力です。\n");
				isError = true;
			}
			if (!std::regex_match(beginDelayText, isFloatForBeginDelay)) {
				errorMessage.append("曲が始まるまでの時間がフォーマットと異なります\n");
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

void Make::Dialog::Make_Dialog_MusicInfo::getMusicInfoFromDlg(char(&filePath)[MAX_PATH], char(&name)[MAX_PATH], char(&artist)[MAX_PATH], std::uint16_t& level, double& bpm, double& totalMinutes, double& beginDelay) {
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
	SetDlgItemText(hDialogWnd, IDC_STATICNAME, "曲名(日本語は対応していません)");
	SetDlgItemText(hDialogWnd, IDC_STATICARTIST, "アーティスト名(日本語は対応していません)");
	SetDlgItemText(hDialogWnd, IDC_STATICLEVEL, "譜面の難易度(1～20)");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM(例:150.68)");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "再生時間(秒)");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "曲が始まるまでの時間(秒)\n例:1.5");

	//EDIITBOXの文字数制限
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITNAME), EM_SETLIMITTEXT, NAMECHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITARTIST), EM_SETLIMITTEXT, ARTISTCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITLEVEL), EM_SETLIMITTEXT, LEVELCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBPM), EM_SETLIMITTEXT, BPMCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITTotalMinutes), EM_SETLIMITTEXT, TOTALMINUTESCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBeginDelay), EM_SETLIMITTEXT, BEGINDELAYCHARMAX, NULL);

	//ダイアログをDXライブラリに登録(DXライブラリは単一のダイアログのみ対応)
	SetDialogBoxHandle(hDialogWnd);

	ShowWindow(hDialogWnd, SW_SHOW);

	while (isShowMusicInfoDlg && ProcessMessage() == 0 &&ClearDrawScreen() == 0) {
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
		char bpmText[BPMCHARMAX] = "";
		GetDlgItemText(hDialogWnd, IDC_EDITBPM, bpmText, BPMCHARMAX);
		bpm = std::stod(bpmText);
		totalMinutes = GetDlgItemInt(hDialogWnd, IDC_EDITTotalMinutes, NULL, true) / Global::MINUTE;
		char beginDelayText[BEGINDELAYCHARMAX] = "";
		GetDlgItemText(hDialogWnd, IDC_EDITBeginDelay, beginDelayText, BEGINDELAYCHARMAX);
		beginDelay = std::stod(beginDelayText);
		if (level < LEVELMIN) {
			level = LEVELMIN;
		}else if(LEVELMAX < level){
			level = LEVELMAX;
		}
	}

	isShowMusicInfoDlg = true;
	isInputed = false;
}