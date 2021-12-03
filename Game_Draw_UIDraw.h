#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Game_File_MusicData.h"
#include "Game_File_MusicFileIO.h"
#include "Game_Draw_RaneDraw.h"

namespace Game {
	namespace Draw {
		class Game_Draw_UIDraw
		{
		private:
			std::unique_ptr<File::Game_File_MusicData> musicData;
			enum MenuID {
				File = 1000,
				NewFile,
				Open,
				Save,
				Exit,
				Test,
				Play,
				Stop,
			};
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//ƒƒjƒ…[‚ª‘I‘ğ‚³‚ê‚½‚çŒÄ‚Î‚ê‚éŠÖ”
		public:
			Game_Draw_UIDraw();
			void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
		};

	}
}