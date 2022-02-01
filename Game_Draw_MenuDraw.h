#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Game_Global.h"
#include "Game_File_MusicData.h"
#include "Game_File_MusicFileIO.h"
#include "Game_File_JsonIO.h"
#include "Game_Draw_LineContainer.h"
#include "Game_Singleton_LaneDraw.h"
#include "Game_Singleton_BeatLineManager.h"

namespace Game {
	namespace Draw {
		class Game_Draw_MenuDraw
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
			};
			static std::shared_ptr<File::Game_File_MusicData> p_musicData;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//メニューが選択されたら呼ばれる関数
		public:
			Game_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
		};

	}
}