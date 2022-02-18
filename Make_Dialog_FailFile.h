#pragma once

#include <dxlib/DxLib.h>
#include <string>
#include <Windows.h>

#include "resource.h"

namespace Make {
	namespace Dialog {
		class Make_Dialog_FailFile
		{
		private:
			static bool isShowMusicInfoDlg;
			static INT_PTR CALLBACK failFileDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		public:
			void failFileDlg(const std::string& sentence);
		};
	}
}

