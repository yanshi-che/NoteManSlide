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
				QUARTER, // ‚S•ª‰¹•„
				EIGHTH, // ‚W•ª‰¹•„
				TRIPLET, // ‚R˜A•„
				SIXTEENTH, // ‚P‚U•ª‰¹•„
				SEXTOLET, // ‚U˜A•„
				THIRTYSECOND, // ‚R‚Q•ª‰¹•„
			};
			enum quontize {
				quarterNote = 1, // ‚S•ª‰¹•„
				eighthNote = 2, // ‚W•ª‰¹•„
				tripletNote = 3, // ‚R˜A•„
				sixteenthNote = 4, // ‚P‚U•ª‰¹•„
				sextoletNote = 6, // ‚U˜A•„
				thirtySecondNote = 8, // ‚R‚Q•ª‰¹•„
			};
			static std::unique_ptr<File::Game_File_MusicData> musicData;
			static Game_Draw_DrawFactory* drawFactory;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//ƒƒjƒ…[‚ª‘I‘ğ‚³‚ê‚½‚çŒÄ‚Î‚ê‚éŠÖ”
		public:
			Game_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
			static void setDrawFactory(Game_Draw_DrawFactory* df);
		};

	}
}