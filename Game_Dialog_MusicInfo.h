#pragma once

#include "resource.h"
#include <Windows.h>
#include <cstdint>
#include "Game_File_BaseFile.h"
#include "Game_Config.h"

namespace Game {
	namespace Dialog {
		boolean isShowMusicInfoDlg = true;
		INT_PTR CALLBACK MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		class Game_Dialog_MusicInfo
		{
		private:
			const double MINUTE;
			const std::uint8_t BPMCHARMAX;
			const std::uint8_t TOTALMINUTESCHARMAX;
			const std::uint8_t BEGINDELAYCHARMAX;
		public:
			Game_Dialog_MusicInfo();
			void getMusicInfoFromDlg(char(&filePath)[MAX_PATH],std::uint8_t& bpm, double& totalMinutes, double& beginDelay);
		};
	}
}
