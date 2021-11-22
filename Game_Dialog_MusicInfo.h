#pragma once

#include "resource.h"
#include <Windows.h>
#include <cstdint>
#include "Game_File_BaseFile.h"
#include "Game_Config.h"

namespace Game {
	namespace Dialog {
		boolean isShowDlg = TRUE;
		INT_PTR CALLBACK MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		class Game_Dialog_MusicInfo
		{
		private:

		public:
			void getMusicInfoFromDlg(char(&filePath)[MAX_PATH],std::uint8_t& bpm, double& totalMinutes, double& beginDlay);
		};
	}
}
