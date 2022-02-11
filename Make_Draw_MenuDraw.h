#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Make_Global.h"
#include "Make_File_MusicData.h"
#include "Make_File_MusicFileIO.h"
#include "Make_File_JsonIO.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Singleton_LaneDraw.h"
#include "Make_Singleton_BeatLineManager.h"

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
				Slide,
			};
			static std::shared_ptr<File::Make_File_MusicData> p_musicData;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//メニューが選択されたら呼ばれる関数
		public:
			Make_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Make_File_MusicData> md);
		};

	}
}