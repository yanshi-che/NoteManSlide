#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Draw {


		void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//メニューが選択されたら呼ばれる関数
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