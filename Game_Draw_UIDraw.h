#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Draw {


		void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//ƒƒjƒ…[‚ª‘I‘ğ‚³‚ê‚½‚çŒÄ‚Î‚ê‚éŠÖ”
		class Game_Draw_UIDraw
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
			};
		public:
			Game_Draw_UIDraw();

		};

	}
}