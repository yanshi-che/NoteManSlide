#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Game_File_MusicData.h"
#include "Game_File_MusicFileIO.h"
#include "Game_Draw_DrawFactory.h"

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
				Exit,
				Test,
				Play,
				Stop,
				QUONTIZE,
				QUARTER, // ４分音符
				EIGHTH, // ８分音符
				TRIPLET, // ３連符
				SIXTEENTH, // １６分音符
				SEXTOLET, // ６連符
				THIRTYSECOND, // ３２分音符
			};
			enum quontize {
				quarterNote = 1, // ４分音符
				eighthNote = 2, // ８分音符
				tripletNote = 3, // ３連符
				sixteenthNote = 4, // １６分音符
				sextoletNote = 6, // ６連符
				thirtySecondNote = 8, // ３２分音符
			};
			static std::unique_ptr<File::Game_File_MusicData> musicData;
			static Game_Draw_DrawFactory drawFactory;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//メニューが選択されたら呼ばれる関数
		public:
			Game_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
		};

	}
}