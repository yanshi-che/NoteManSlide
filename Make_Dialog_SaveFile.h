#pragma once

#include <dxlib/DxLib.h>
#include <cstdint>
#include <Windows.h>

#include "Make_File_BaseFile.h"
#include "resource.h"

namespace Make {
	namespace Dialog {
		class Make_Dialog_SaveFile
		{
		private:
			static bool isShowMusicInfoDlg;
			static bool isInputed;
			static INT_PTR CALLBACK saveFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		public:
			void getSaveFilePathFromDlg(char(&saveFilePath)[MAX_PATH], char(&musicFilePath)[MAX_PATH]);
		};
	}
}

