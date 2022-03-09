#pragma once

#include <functional>
#include <memory>
#include <tuple>
#include <utility>

#include "dxlib/DxLib.h"
#include "boost/json.hpp"
#include "SceneChanger.h"
#include "Make_Global.h"
#include "Make_File_MusicData.h"
#include "Make_File_MusicFileIO.h"
#include "Make_File_JsonIO.h"
#include "Make_File_SaveFileIO.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Draw_BeatLineManager.h"
#include "Make_Play_MusicPlayer.h"
#include "Make_Play_TestPlayManager.h"

using namespace boost;

namespace Make {
	namespace Draw {
		class Make_Draw_MenuDraw
		{
		private:
			enum MenuID {
				File = 1000,
				NewFile,
				Open,
				Save,
				Export,
				Exit,
				Test,
				Play,
				Stop,
				WholeQUONTIZE, //全体のクオンタイズの変更
				WholeQUARTER,
				WholeEIGHTH,
				WholeTRIPLET,
				WholeSIXTEENTH,
				WholeTHIRTYSECOND,
				PartQUONTIZE, //一部のクオンタイズの変更
				PartQUARTER,
				PartEIGHTH,
				PartTRIPLET,
				PartSIXTEENTH,
				PartTHIRTYSECOND,
				NoteType,//ノーツの種類の変更
				Normal,
				Long,
				SlideR,
				SlideL
			};
			static std::shared_ptr<SceneChanger> sceneChanger;
			static std::shared_ptr<File::Make_File_MusicData> p_musicData;
			static std::shared_ptr<Play::Make_Play_MusicPlayer> p_musicPlayer;
			static std::shared_ptr<Play::Make_Play_TestPlayManager> p_testPlay;
			static std::shared_ptr<Draw::Make_Draw_BeatLineManager> p_beatLine;
			static std::function<void()> drawFunc;
			static bool isPlaying;
			static bool isFileOpen;

			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//メニューが選択されたら呼ばれる関数
			static void setMusicDataFromNewFile(const std::shared_ptr<File::Make_File_MusicData> md);
			static void setMusicDataFromSaveFile(std::unique_ptr<File::Make_File_MusicData> md, const json::value val);
		public:
			Make_Draw_MenuDraw(std::shared_ptr<SceneChanger>& sceneChanger);
			void finalize();
			void resetDrawFunc();
			std::function<void()> getDrawFunc();
		};

	}
}