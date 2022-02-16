#include "Make_Dialog_MusicInfo.h"

bool Make::Dialog::Make_Dialog_MusicInfo::isShowMusicInfoDlg = true;
bool Make::Dialog::Make_Dialog_MusicInfo::isInputed = false;

INT_PTR CALLBACK Make::Dialog::Make_Dialog_MusicInfo::MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case IDC_BUTTONFilePath:
		{
			const char* title[] = { "���y�t�@�C���̑I��" };
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
	//���C���E�B���h�E�n���h���̕ۑ�
	hMainWnd = GetMainWindowHandle();
	hInstance = GetModuleHandle(nullptr);

	//�_�C�A���O�̍쐬
	hDialogWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MUSICINFO), hMainWnd, MusicInfoDialogProc);

	//�e���ڂ̐����̐ݒ�
	SetDlgItemText(hDialogWnd, IDC_BUTTONFilePath, "�t�@�C���I��");
	SetDlgItemText(hDialogWnd, IDC_STATICNAME, "�Ȗ�(���{����͂ł��Ȃ��ꍇ�̓y�[�X�g���Ă�������)");
	SetDlgItemText(hDialogWnd, IDC_STATICARTIST, "�A�[�e�B�X�g��");
	SetDlgItemText(hDialogWnd, IDC_STATICLEVEL, "���ʂ̓�Փx(1�`20)");
	SetDlgItemText(hDialogWnd, IDC_STATICBPM, "BPM");
	SetDlgItemText(hDialogWnd, IDC_STATICTotalMinutes, "�Đ�����(�b)");
	SetDlgItemText(hDialogWnd, IDC_STATICBeginDelay, "�Ȃ��n�܂�܂ł̎���(�b)");
	SetDlgItemText(hDialogWnd, IDC_STATICLANE, "���[����(4�`8)");

	//EDIITBOX�̕���������
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITNAME), EM_SETLIMITTEXT, NAMECHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITARTIST), EM_SETLIMITTEXT, ARTISTCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITLEVEL), EM_SETLIMITTEXT, LEVELCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBPM), EM_SETLIMITTEXT, BPMCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITTotalMinutes), EM_SETLIMITTEXT, TOTALMINUTESCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITBeginDelay), EM_SETLIMITTEXT, BEGINDELAYCHARMAX, NULL);
	SendMessage(GetDlgItem(hDialogWnd, IDC_EDITLANE), EM_SETLIMITTEXT, amountOfLaneCHARMAX, NULL);

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