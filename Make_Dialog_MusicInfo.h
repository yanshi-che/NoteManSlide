#pragma once

#include <cstdint>
#include <regex>
#include <Windows.h>

#include "Global.h"
#include "Singleton_FpsOperator.h"
#include "Make_File_BaseFile.h"
#include "resource.h"

namespace Make {
	namespace Dialog {
		constexpr const std::uint16_t NAMECHARMAX{50};
		constexpr const std::uint16_t ARTISTCHARMAX{50};
		constexpr const std::uint16_t LEVELCHARMAX{2};
		constexpr const std::uint16_t BPMCHARMAX{6};
		constexpr const std::uint16_t TOTALMINUTESCHARMAX{4};
		constexpr const std::uint16_t BEGINDELAYCHARMAX{5};
		constexpr const std::uint16_t LEVELMAX{ 20 };
		constexpr const std::uint16_t LEVELMIN{ 1 };
		constexpr const std::uint16_t LANEMAX{8};
		constexpr const std::uint16_t LANEMIN{4};
		class Make_Dialog_MusicInfo
		{
		private:
			static bool isShowMusicInfoDlg;
			static bool isInputed;
			static INT_PTR CALLBACK MusicInfoDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		public:
			void getMusicInfoFromDlg(char(&filePath)[MAX_PATH], char(&name)[MAX_PATH],char(&artist)[MAX_PATH],std::uint16_t& level,double& bpm, double& totalMinutes, double& beginDelay);
		};
	}
}
