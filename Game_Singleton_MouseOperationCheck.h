#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_MouseOperationCheck
		{
		private:
			static Game_Singleton_MouseOperationCheck* p_instance;
			Game_Singleton_MouseOperationCheck();
		public:
			static  Game_Singleton_MouseOperationCheck* getInstance();
			void destroyInstance();
			int  mouseX, mouseY; //マウスのクリック管理
			int button, logType;//マウスのクリック管理
			bool isMouseClickLeftDown();
			bool isMouseClickLeftUp();

		};
	}
}

