#pragma once

#include "dxlib/DxLib.h"

namespace Make {
	namespace Singleton {
		class Make_Singleton_MouseOperationCheck
		{
		private:
			static Make_Singleton_MouseOperationCheck* p_instance;
			Make_Singleton_MouseOperationCheck();
			bool mouseClickLeftDown, mouseClickLeftUp;
			int mouseX, mouseY;//マウスクリックの座標格納用の変数
			int button, logType;//マウスのクリック管理
		public:
			static Make_Singleton_MouseOperationCheck* getInstance();
			static void destroyInstance();
			void checkMouseClick();//必要となる処理の最上位の処理で呼ぶこと
			bool isMouseClickLeftDown(int& x, int& y);//座標の獲得にはこれを使う
			bool isMouseClickLeftUp(int& x, int& y);//座標の獲得にはこれを使う
		};
	}
}

