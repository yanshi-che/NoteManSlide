#pragma once

#include "resource.h"
#include <Windows.h>
#include <cstdint>
#include "Game_File_BaseFile.h"

namespace Game {
	namespace Dialog {
		class Game_Dialog_MusicInfo
		{
		private:
			static bool isShowMusicInfoDlg;
			static bool isInputed;
			static INT_PTR CALLBACK MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			const double MINUTE;
			const std::uint8_t BPMCHARMAX;
			const std::uint8_t TOTALMINUTESCHARMAX;
			const std::uint8_t BEGINDELAYCHARMAX;
			const std::uint8_t NUMBEROFRANECHARMAX;
			const std::uint8_t RANEMAX;
			const std::uint8_t RANEMIN;
		public:
			Game_Dialog_MusicInfo();
			void getMusicInfoFromDlg(char(&filePath)[MAX_PATH],std::uint16_t& bpm, double& totalMinutes, double& beginDelay,std::uint8_t& numberOfRane);
		};
	}
}
