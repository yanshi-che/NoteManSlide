#pragma once

#include "resource.h"
#include <Windows.h>
#include <cstdint>
#include "Make_Global.h"
#include "Make_File_BaseFile.h"

namespace Make {
	namespace Dialog {
		class Make_Dialog_MusicInfo
		{
		private:
			static bool isShowMusicInfoDlg;
			static bool isInputed;
			static INT_PTR CALLBACK MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			const std::uint8_t BPMCHARMAX;
			const std::uint8_t TOTALMINUTESCHARMAX;
			const std::uint8_t BEGINDELAYCHARMAX;
			const std::uint8_t amountOfLaneCHARMAX;
			const std::uint8_t RANEMAX;
			const std::uint8_t RANEMIN;
		public:
			Make_Dialog_MusicInfo();
			void getMusicInfoFromDlg(char(&filePath)[MAX_PATH], std::uint16_t& bpm, float& totalMinutes, std::uint16_t& beginDelay, std::uint8_t& amountOfLane);
		};
	}
}
