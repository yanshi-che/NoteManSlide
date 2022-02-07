#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_MouseOperationCheck
		{
		private:
			static Game_Singleton_MouseOperationCheck* p_instance;
			Game_Singleton_MouseOperationCheck();
			bool mouseClickLeftDown, mouseClickLeftUp;
			int mouseX, mouseY;//マウスクリックの座標格納用の変数
			int button, logType;//マウスのクリック管理
		public:
			static  Game_Singleton_MouseOperationCheck* getInstance();
			void destroyInstance();
			void checkMouseClick();//必要となる処理の最上位の処理で呼ぶこと
			bool isMouseClickLeftDown(int& x, int& y);//座標の獲得にはこれを使う
			bool isMouseClickLeftUp(int& x, int& y);//座標の獲得にはこれを使う
		};
	}
}

